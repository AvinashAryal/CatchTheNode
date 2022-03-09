#pragma once

#define H 960 
#define W 1800

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <cstdlib>
#include <string>
#include <vector>

class Visualizer
{
    SDL_Window *w;
    SDL_Renderer *r;
    SDL_Event e;
    bool addEdge, addVertex, doBFS, startBFS, doDFS, startDFS, doDijkstra, startDijkstra;
    bool clearAlg,clearGraph;
    int v1,v2,bfs_start_point,dfs_start_point,dijkstra_start_point;
    SDL_Rect add_edge_button,add_vertex_button,window_rect,bfs_button,dfs_button,dijkstra_button,clear_button,clear_graph_button,start_button,startmenu_rect;
    SDL_Texture *vertex_tex,*scanned_vertex_tex,*edge_tex,*scanned_edge_tex,*edge_weight_tex,*vertex_dist_tex;
    SDL_Texture *add_vertex_tex,*add_vertex_hovered_tex,*add_edge_tex,*add_edge_hovered_tex,*start_tex,*start_hovered_tex,*startmenu;
    SDL_Texture *bfs_tex,*bfs_hovered_tex,*dfs_tex,*dfs_hovered_tex,*clear_tex,*clear_hovered_tex,*clear_graph_tex,*clear_graph_hovered_tex,*dijkstra_tex,*dijkstra_hovered_tex;
    SDL_Point mouse_pos;
    long t1 = 0;
    public:
    bool startVis;
    Visualizer()
    {
        add_vertex_button = {220,H-90,160,80};
        add_edge_button = {420,H-90,160,80};
        bfs_button = {620,H-90,160,80};
        dfs_button = {820,H-90,160,80};
        dijkstra_button = {1020,H-90,160,80};
        clear_button = {1220,H-90,160,80};
        clear_graph_button = {1420,H-90,160,80};
        window_rect = {0,0,W,H-100};
        startmenu_rect = {0,0,W,H};
        start_button = {750,570,300,150};
        doBFS = addEdge = addVertex = startBFS = doDFS = startDFS = doDijkstra = startDijkstra = false;
        clearAlg = clearGraph = false;
        startVis = false;
        v1 = v2 = -1;
    }
    bool isRunning = true;
    void Start();
    void DrawStartMenu();
    void ShowVertex();
    void ShowEdge();
    void HandleEvents();
    void Show();
    void Stop();
    void Destroy();
};




