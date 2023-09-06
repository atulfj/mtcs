#!/usr/bin/env python
# coding: utf-8

import pandas as pd
import requests
from bs4 import BeautifulSoup
from bertopic import BERTopic

urls = pd.read_csv('../tables/urls.csv')

headers = requests.utils.default_headers()
headers.update(
    {
        'User-Agent': 'Custom User Agent 1.0',
        'From': 'vivekg22@iitk.ac.in'  
    }
)

tm10 = BERTopic.load("../models/tm_10")
en_stop = ["Google", "Search"]


def get_url_title(url):
    if(len(url)>5):
        try:
            r = requests.get(url, headers=headers, timeout=10)
        except:
            r = ''
            pass
        if(type(r)!=str):
            soup = BeautifulSoup(r.text, 'lxml')
            if(len(soup('title'))>0):
                if(soup('title')[0].string is not None):
                    title = soup('title')[0].string.encode('utf-8').strip().decode()     
                else:
                    title = None
            else:
                title = None
        else:
            title = None
    return [title]


def get_topic(url, use_table=False):
    title = []

    if use_table:
        title = [urls.query(f"id=={url}").title.item()]
    else:
        title = get_url_title(url)
    if not title[0]:
        return None
    
    words = str(title[0]).split(' ')
    new_words = ""
    for word in words:
        if word not in en_stop:
            new_words += word + " "

    title[0] = new_words
    topic = tm10.transform(title)
    
    return topic




