from vtk import *
import numpy as np

# HELPER FUNCTIONS

def extractCell(data, cellId):
    '''
    Parameters:
    data: Image data
    cellId: Cell ID

    Returns:
    List of point IDs stored in counter-clockwise order
    '''
    cell = data.GetCell(cellId)
    return [cell.GetPointId(i) for i in [0,1,3,2]]

def getContourPointCoords(data, arr, cellPoints, value):
    '''
    Parameters:
    data: Image data
    arr: vtk array with attribute values
    cellPoints: point IDs of cell
    value: Isocontour value

    Returns:
    A 2D list containing isocontour points' coordinates
    '''
    coords = []
    n = len(cellPoints)
    
    for i in range(n):
        p1 = np.array(data.GetPoint(cellPoints[i]))
        p2 = np.array(data.GetPoint(cellPoints[(i+1)%n]))
        v1 = arr.GetTuple1(cellPoints[i])
        v2 = arr.GetTuple1(cellPoints[(i+1)%n])
        if v2 < value < v1:
            p = ((v1-value)/(v1-v2))*(p2-p1) + p1
            coords.append(list(p))
        if v1 < value < v2:
            p = ((v2-value)/(v2-v1))*(p1-p2) + p2
            coords.append(list(p))
    
    return coords

# Take isocontour value as input
value = float(input("Enter isocontour value: "))

# Read data
reader = vtkXMLImageDataReader()
reader.SetFileName('Data/Isabel_2D.vti')
reader.Update()
data = reader.GetOutput()

# Store total number of cells
totalCells = data.GetNumberOfCells()

# Extract Pressure array
pressArray = data.GetPointData().GetArray('Pressure')

isocon = [] # stores contour points' coordinates

for i in range(0, totalCells):
    points = extractCell(data, i)
    coords = getContourPointCoords(data, pressArray, points, value)
    if(len(coords)):
        isocon += coords

points = vtkPoints()
cells = vtkCellArray()

# Insert points in vtkPoints
for point in isocon:
    points.InsertNextPoint(point)
    
for i in range(0, len(isocon), 2):
    polyLine = vtkPolyLine()
    polyLine.GetPointIds().SetNumberOfIds(2)
    polyLine.GetPointIds().SetId(0, i)
    polyLine.GetPointIds().SetId(1, i+1)
    cells.InsertNextCell(polyLine)

pdata = vtkPolyData()
pdata.SetPoints(points)
pdata.SetLines(cells)

# Write the polydata to a vtp file
writer = vtkXMLPolyDataWriter()
writer.SetInputData(pdata)
writer.SetFileName("isocontour.vtp")
writer.Write()


# Read isocontour dot vtp file
reader = vtk.vtkXMLPolyDataReader()
reader.SetFileName("isocontour.vtp")
reader.Update()
data = reader.GetOutput()

# Mapper -> Actor -> Renderer pipeline
mapper = vtkPolyDataMapper()
mapper.SetInputData(data)

colors = vtkNamedColors()

actor = vtkActor()
actor.SetMapper(mapper)
actor.GetProperty().SetLineWidth(1)
actor.GetProperty().SetColor(colors.GetColor3d('Tomato'))

renderer = vtkRenderer()
renderWindow = vtkRenderWindow()
renderer.SetBackground(colors.GetColor3d('DarkOliveGreen'))
renderWindow.SetSize(1000,1000)
renderWindow.SetWindowName(f"Isocontour at value {value}")
renderWindow.AddRenderer(renderer)
renderWindowInteractor = vtkRenderWindowInteractor()
renderWindowInteractor.SetRenderWindow(renderWindow)
renderer.AddActor(actor)

renderWindow.Render()
renderWindowInteractor.Start()
