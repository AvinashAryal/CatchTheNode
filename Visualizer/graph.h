#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <cstdlib>
#include <list>
#include <stack>
#include <string>

using namespace std;

class Vertex
{
    public:
    SDL_Rect v_rect,text_rect;
    SDL_Surface *vertex_surf,*dist_surf;
    vector<int> adj;
    bool visited;
    int dist;
    Vertex()
    {
        vertex_surf = IMG_Load("images/vertex.png");
        visited = false;
        v_rect.x = v_rect.y = v_rect.w = v_rect.h = 0;
    }
};

class Edge
{
    public:
    int x1,x2,y1,y2;
    int v1,v2;
    bool visited;
    SDL_Rect edge_rect,text_rect;
    SDL_Surface *edge_surf,*text_surf;
    int angle;
    int weight;
    Edge()
    {
        visited = false;
        edge_surf = IMG_Load("images/edge.png");
    }
};

class Graph
{
    public:
        list<int> queue;
        stack<int> Stack;
        vector<Vertex> v;
        vector<Edge> e;
        int last_popped;
        TTF_Font *text_font,*text_font2;
        SDL_Color col,col2;
        bool doBFS;
        bool doDFS;
        bool doDijkstra,isColored;
        bool Dijkstra_called;
        void AddVertex(int,int);
        void AddEdge(int, int);
        void BFS(int);
        void DFS(int);
        void Dijkstra(int);
        void clearAlg();
        void clearGraph();
        void PrintGraph();
        Graph()
        {
            col = {200,200,200,255};
            col2 = {1,50,32,255};
            doBFS = false;
            doDFS = false;
            doDijkstra = isColored = false;
            Dijkstra_called = false;
        }
};


