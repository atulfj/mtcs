from vtk import *

# Enable Phong shading?
phong = input("Enable Phong shading? [y/n]: ")

# Read data
reader = vtkXMLImageDataReader()
reader.SetFileName('Data/Isabel_3D.vti')
reader.Update()
data = reader.GetOutput()

# Create color and opacity transfer functions
colorTransferFunc = vtkColorTransferFunction()
colorTransferFunc.AddRGBPoint(-4931.54,0,1,1)
colorTransferFunc.AddRGBPoint(-2508.95,0,0,1)
colorTransferFunc.AddRGBPoint(-1873.9,0,0,0.5)
colorTransferFunc.AddRGBPoint(-1027.16,1,0,0)
colorTransferFunc.AddRGBPoint(-298.031,1,0.4,0)
colorTransferFunc.AddRGBPoint(2594.97,1,1,0)

opacityTransferFunc = vtkPiecewiseFunction()
opacityTransferFunc.AddPoint(-4931.54,1.0)
opacityTransferFunc.AddPoint(101.815,0.002)
opacityTransferFunc.AddPoint(2594.97,0.0)

# Generate volume properties
volProp = vtkVolumeProperty()
volProp.SetColor(colorTransferFunc)
volProp.SetScalarOpacity(opacityTransferFunc)
if phong=="y":
    volProp.ShadeOn()
    volProp.SetAmbient(0.5)
    volProp.SetDiffuse(0.5)
    volProp.SetSpecular(0.5)

colors = vtkNamedColors()

# Outline filter
outlineFilter = vtkOutlineFilter()
outlineFilter.SetInputData(data)
outlineFilter.Update()

# Outline mapper -> Actor -> Renderer
outlineMapper = vtkPolyDataMapper()
outlineMapper.SetInputConnection(outlineFilter.GetOutputPort())
outline = vtkActor() # outline actor
outline.SetMapper(outlineMapper)
outline.GetProperty().SetColor(colors.GetColor3d('DarkOliveGreen'))

# Volume mapper -> Actor -> Renderer pipeline
volMapper = vtkSmartVolumeMapper()
volMapper.SetInputData(data)

volume = vtkVolume() # volume actor
volume.SetMapper(volMapper)
volume.SetProperty(volProp)

renderer = vtkRenderer()
renderWindow = vtkRenderWindow()
renderer.SetBackground(colors.GetColor3d('White'))
renderWindow.SetSize(1000,1000)
renderWindow.SetWindowName("Isabel 3D")
renderWindow.AddRenderer(renderer)
renderWindowInteractor = vtkRenderWindowInteractor()
renderWindowInteractor.SetRenderWindow(renderWindow)
renderer.AddActor(volume)
renderer.AddActor(outline)

renderWindow.Render()
renderWindowInteractor.Start()
