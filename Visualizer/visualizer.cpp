#pragma once

#include "visualizer.h"
#include "graph.h"
#include "graph.cpp"

Graph *g = new Graph;

void Visualizer::Start()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" );
    w = SDL_CreateWindow("Visualizer",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, W,H,0); 
    r = SDL_CreateRenderer(w,-1,0);
    add_vertex_tex = IMG_LoadTexture(r,"images/add_vertex.png");
    add_vertex_hovered_tex = IMG_LoadTexture(r,"images/add_vertex_hovered.png");
    add_edge_tex = IMG_LoadTexture(r,"images/add_edge.png");
    add_edge_hovered_tex = IMG_LoadTexture(r,"images/add_edge_hovered.png");
    dfs_tex = IMG_LoadTexture(r, "images/dfs.png");
    dfs_hovered_tex = IMG_LoadTexture(r, "images/dfs_hovered.png");
    bfs_tex = IMG_LoadTexture(r, "images/bfs.png");
    dijkstra_tex = IMG_LoadTexture(r, "images/dijkstra.png");
    dijkstra_hovered_tex = IMG_LoadTexture(r, "images/dijkstra_hovered.png");
    bfs_hovered_tex = IMG_LoadTexture(r, "images/bfs_hovered.png");
    clear_tex = IMG_LoadTexture(r, "images/clear.png");
    clear_hovered_tex = IMG_LoadTexture(r, "images/clear_hovered.png");
    clear_graph_tex = IMG_LoadTexture(r, "images/clear_graph.png");
    clear_graph_hovered_tex = IMG_LoadTexture(r, "images/clear_graph_hovered.png");
    startmenu = IMG_LoadTexture(r,"images/startmenu.png");
    start_tex = IMG_LoadTexture(r,"images/start_button.png");
    start_hovered_tex = IMG_LoadTexture(r,"images/start_button_hovered.png");
}

void Visualizer::DrawStartMenu()
{
    SDL_RenderClear(r);
    SDL_PollEvent(&e);
    SDL_GetMouseState(&mouse_pos.x, &mouse_pos.y);
    if(e.type == SDL_QUIT) isRunning = false;
    if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
    {
        if(SDL_PointInRect(&mouse_pos,&start_button)) startVis = true;
    }
    SDL_RenderCopy(r,startmenu,NULL,&startmenu_rect);
    if(SDL_PointInRect(&mouse_pos,&start_button)) SDL_RenderCopy(r,start_hovered_tex,NULL,&start_button);
    else SDL_RenderCopy(r,start_tex,NULL,&start_button);
    SDL_RenderPresent(r);
}

void Visualizer::ShowVertex()
{
    for(int i = 0;i < (g->v.size());i++ )
    {
          vertex_tex = SDL_CreateTextureFromSurface(r,g->v[i].vertex_surf);
          if(vertex_tex == NULL) std::cout << "Error" << std::endl;
          SDL_RenderCopy(r,vertex_tex,NULL,&(g->v[i].v_rect));
          SDL_DestroyTexture(vertex_tex);
    }
    if(startDijkstra)
    {
        for(int i = 0; i < (g->v.size());i++)
        { 
            vertex_dist_tex = SDL_CreateTextureFromSurface(r,g->v[i].dist_surf);
            SDL_RenderCopy(r,vertex_dist_tex,NULL,&(g->v[i].text_rect));
            SDL_DestroyTexture(vertex_dist_tex);
        }
    }
}

void Visualizer::ShowEdge()
{
    for(int i = 0;i < g->e.size();i++)
    {
        edge_tex = SDL_CreateTextureFromSurface(r, g->e[i].edge_surf);
        if(edge_tex == NULL) std::cout << "Error" << std::endl;
        SDL_RenderCopyEx(r,edge_tex,NULL,&(g->e[i].edge_rect),90 - g->e[i].angle,NULL,SDL_FLIP_NONE);
        SDL_DestroyTexture(edge_tex);
    }
    if(doDijkstra)
    {
        for(int i = 0; i < g->e.size();i++)
        {
            edge_weight_tex = SDL_CreateTextureFromSurface(r, g->e[i].text_surf);
            SDL_RenderCopy(r,edge_weight_tex,NULL,&(g->e[i].text_rect));
            SDL_DestroyTexture(edge_weight_tex);
        }
    }
}

void Visualizer::HandleEvents()
{
    SDL_PollEvent(&e);
    switch(e.type)
    {
    case SDL_MOUSEBUTTONDOWN:
    {
    long t2 = SDL_GetTicks();
    SDL_GetMouseState(&mouse_pos.x, &mouse_pos.y);
    if(e.button.button == SDL_BUTTON_LEFT)
    {
    SDL_GetMouseState(&mouse_pos.x, &mouse_pos.y);
    if(SDL_PointInRect(&mouse_pos,&bfs_button))
    {
        doBFS = true;
        doDFS = false;
        addEdge = false;
        addVertex = false;
        doDijkstra = false;
    }
    if(SDL_PointInRect(&mouse_pos,&dfs_button))
    {
        doDFS = true;
        addEdge = false;
        addVertex = false;
        doBFS = false;
        doDijkstra = false;
    }
    if(SDL_PointInRect(&mouse_pos,&add_edge_button))
    {
        addEdge = true;
        addVertex = false;
        doBFS = false;
        doDijkstra = false;
        doDFS = false;
    }
    if(SDL_PointInRect(&mouse_pos,&add_vertex_button))
    {
        addVertex = true;
        addEdge = false;
        doBFS = false;
        doDFS = false;
        doDijkstra = false;
    }
    if(SDL_PointInRect(&mouse_pos,&dijkstra_button))
    {
        doDijkstra = true;
        addVertex = false;
        addEdge = false;
        doBFS = false;
        doDFS = false;
    }
    if(SDL_PointInRect(&mouse_pos,&clear_button))
    {
        addEdge = addVertex = doBFS =  startBFS = doDFS = startDFS = doDijkstra = startDijkstra = false;
        g->clearAlg();
    }
    if(SDL_PointInRect(&mouse_pos,&clear_graph_button))
    {
        addEdge = addVertex = doBFS =  startBFS = doDFS = startDFS = doDijkstra = startDijkstra = false;
        g->clearGraph();
    }
    if(doBFS)
    {
        for(int i = 0;i < g->v.size();i++)
        {
            SDL_GetMouseState(&mouse_pos.x, &mouse_pos.y);
            if(SDL_PointInRect(&mouse_pos,&(g->v[i].v_rect)))
            {
                startBFS = true;
                bfs_start_point = i;
                break;
            }
        }
    }
    if(doDFS)
    {
        for(int i = 0;i < g->v.size();i++)
        {
            SDL_GetMouseState(&mouse_pos.x, &mouse_pos.y);
            if(SDL_PointInRect(&mouse_pos,&(g->v[i].v_rect)))
            {
                startDFS =  true;
                dfs_start_point = i;
                break;
            }
        }
    }
    if(doDijkstra)
    {
        for(int i = 0;i < g->v.size();i++)
        {
            SDL_GetMouseState(&mouse_pos.x, &mouse_pos.y);
            if(SDL_PointInRect(&mouse_pos,&(g->v[i].v_rect)))
            {
                startDijkstra =  true;
                dijkstra_start_point = i;
                break;
            } 
      }
    }
    if(addEdge)
     {
        if(v1 > -1 && t2-t1 > 150)
        {
            for(int i = 0;i < g->v.size();i++)
            {
                if(SDL_PointInRect(&mouse_pos,&(g->v[i].v_rect)))
                {
                    v2 = i;
                    if( g->v.size() >= 1 && v1 != v2) g->AddEdge(v1, v2);
                    v1 = -1;
                    break;
                }
            }
        }
        for(int i = 0;i < g->v.size();i++)
        {
            if(SDL_PointInRect(&mouse_pos,&(g->v[i].v_rect)) && t2-t1 > 150)
            {
                if(addEdge && v2 == -1) v1 = i;
                break;
            }
        }
        v2 = -1;
    }
    if(addVertex && SDL_PointInRect(&mouse_pos,&window_rect) && (t2-t1 > 150))
    {
        v1 = v2 = -1;
        SDL_GetMouseState(&mouse_pos.x,&mouse_pos.y);
        g->AddVertex(e.button.x, e.button.y);
    }
    t1 = t2;
    }
    break;
    }
    case SDL_QUIT:
    {
        isRunning = false;
        break;
    }
    break;
    }
}

void Visualizer::Show()
{
    SDL_RenderClear(r);
    if(startBFS) g->BFS(bfs_start_point);
    if(startDFS) g->DFS(dfs_start_point);
    if(startDijkstra) g->Dijkstra(dijkstra_start_point);
    SDL_DestroyTexture(startmenu);
//    std::cout << g->v.size() << g->e.size() << std::endl;
    SDL_GetMouseState(&mouse_pos.x,&mouse_pos.y);
    if(SDL_PointInRect(&mouse_pos,&add_vertex_button) || addVertex) SDL_RenderCopy(r,add_vertex_hovered_tex,NULL,&add_vertex_button);
    else SDL_RenderCopy(r,add_vertex_tex,NULL,&add_vertex_button);
    if(SDL_PointInRect(&mouse_pos,&add_edge_button) || addEdge) SDL_RenderCopy(r,add_edge_hovered_tex,NULL,&add_edge_button);
    else SDL_RenderCopy(r,add_edge_tex,NULL,&add_edge_button);
    if(SDL_PointInRect(&mouse_pos,&bfs_button) || doBFS) SDL_RenderCopy(r,bfs_hovered_tex,NULL,&bfs_button);
    else SDL_RenderCopy(r,bfs_tex,NULL,&bfs_button);
    if(SDL_PointInRect(&mouse_pos,&dfs_button) || doDFS) SDL_RenderCopy(r,dfs_hovered_tex,NULL,&dfs_button);
    else SDL_RenderCopy(r,dfs_tex,NULL,&dfs_button);
    if(SDL_PointInRect(&mouse_pos,&dijkstra_button) || doDijkstra) SDL_RenderCopy(r,dijkstra_hovered_tex,NULL,&dijkstra_button);
    else SDL_RenderCopy(r,dijkstra_tex,NULL,&dijkstra_button);
    if(SDL_PointInRect(&mouse_pos,&clear_button)) SDL_RenderCopy(r,clear_hovered_tex,NULL,&clear_button);
    else SDL_RenderCopy(r,clear_tex,NULL,&clear_button);
    if(SDL_PointInRect(&mouse_pos,&clear_graph_button)) SDL_RenderCopy(r,clear_graph_hovered_tex,NULL,&clear_graph_button);
    else SDL_RenderCopy(r,clear_graph_tex,NULL,&clear_graph_button);
    ShowEdge();
    ShowVertex();
    SDL_SetRenderDrawColor(r,40,40,40,255);
    SDL_RenderPresent(r);
}

void Visualizer::Destroy()
{
    SDL_DestroyWindow(w);
    SDL_DestroyRenderer(r);
    SDL_Quit();
}
