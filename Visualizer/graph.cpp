#pragma once

#include "graph.h"

void Graph::AddVertex(int mouseX, int mouseY)
{
    SDL_Point clicked_point = {mouseX,mouseY};
    for(int i = 0;i < v.size();i++)
    {
        if(mouseX > v[i].v_rect.x - 25 && mouseX < v[i].v_rect.x + 75 && mouseY > v[i].v_rect.y - 25 && mouseY < v[i].v_rect.y + 75) return;
    }
    Vertex *v_temp = new Vertex;
    v_temp->v_rect.x = mouseX - 25; 
    v_temp->v_rect.y = mouseY - 25; 
    v_temp->v_rect.w = 50; 
    v_temp->v_rect.h = 50; 
    v_temp->text_rect.x = v_temp->v_rect.x + 10; 
    v_temp->text_rect.y = v_temp->v_rect.y + 10; 
    v_temp->text_rect.w = 30; 
    v_temp->text_rect.h = 30; 
    v.push_back(*v_temp);
    delete v_temp;
}

void Graph::AddEdge(int a, int b)
{
    for(auto i:v[a].adj)
    {
        if(i == b) return;
    }
    Edge *temp_edge = new Edge;
    temp_edge->v1 = a;
    temp_edge->v2 = b;
    int x1 = v[a].v_rect.x + 25;
    int y1 = v[a].v_rect.y + 25;
    int x2 = v[b].v_rect.x + 25;
    int y2 = v[b].v_rect.y + 25;
    float xmid = (x1 + x2)/2;
    float ymid = (y1 + y2)/2;
    float dely = (y2 - ymid);
    float delx = (x2 - xmid);
    float dist = sqrt(pow(delx,2) + pow(dely,2));
    temp_edge->angle = (asin(delx/dist)*180)/3.1415;
    if(y1 > y2) temp_edge->angle = 180 - temp_edge->angle;
    temp_edge->edge_rect = {int(xmid - dist),int(ymid - 3),int(2*dist),6};
    temp_edge->weight = int(2*dist);
    string str = std::to_string(int(2*dist));
    text_font = TTF_OpenFont("font/font.ttf",100);
    if(text_font == NULL) std::cout<< "Error" << std::endl;
    temp_edge->text_surf = TTF_RenderText_Solid(text_font,str.c_str(),col);
    temp_edge->text_rect = {int(xmid - 20),int(ymid - 15),40,30};
    e.push_back(*temp_edge);
    v[a].adj.push_back(b);
    v[b].adj.push_back(a);
    delete(temp_edge);
}

void Graph::BFS(int s)
{
    doBFS = false;
    for(int i = 0; i < v.size();i++)
    {
        if(!v[i].visited && v[i].adj.size() != 0)
         {
            doBFS = true;
            break;
        }
    }
    if(queue.empty() && doBFS)
    {
      v[s].visited = true;
      v[s].vertex_surf = IMG_Load("images/vertex_scanned.png");
      queue.push_back(s);
    }
    if(!doBFS) return;
    else
    {
    s = queue.front();
    queue.pop_front();
    for(auto i: v[s].adj)
    {
        if(!v[i].visited)
        {
            for(int j = 0;j < e.size();j++)
            {
                if ((e[j].v1 == s && e[j].v2 == i)||(e[j].v2 == s && e[j].v1 == i))
                {
                    e[j].edge_surf = IMG_Load("images/edge_scanned.png");
                }
            }
            v[i].visited = true;
            v[i].vertex_surf = IMG_Load("images/vertex_scanned.png");
            queue.push_back(i);
        }
    }
    SDL_Delay(1000);
    }
}

void Graph::DFS(int s)
{
    doDFS = false;
    for(int i = 0; i < v.size();i++)
    {
        if(!v[i].visited && v[i].adj.size() != 0)
        {
            doDFS = true;
            break;
        }
    }
    if(Stack.empty() && doDFS)
    {
        Stack.push(s);
    }
    if(!doDFS) return;
    else
    {
    s = Stack.top();
    Stack.pop();
    if(!v[s].visited)
    {
        for(int j = 0;j < e.size();j++)
        {
//            if( ((e[j].v1 == s) && (e[j].v2 == last_popped)) || ((e[j].v2 == s) && (e[j].v1 == last_popped)) )
//            {
//                e[j].edge_surf = IMG_Load("images/scanned_edge.png");
//                continue;
//            }
             if ( ((e[j].v1 == s) && v[e[j].v2].visited) || ((e[j].v2 == s) && v[e[j].v1].visited) )
                 e[j].edge_surf = IMG_Load("images/edge_scanned.png");
        }
        last_popped = s;
        v[s].visited = true;
        v[s].vertex_surf = IMG_Load("images/vertex_scanned.png");
    }
    for(auto i: v[s].adj)
    {
        for(int j = 0; j < e.size();j++)
        {
            if((e[j].v1 == i && e[j].v2 == s) || (e[j].v2 == i && e[j].v1 == s)) e[j].visited = true;
        }
        if(!v[i].visited)
        {
            Stack.push(i);
        }
    }
    SDL_Delay(1000);
    }
}

void Graph::Dijkstra(int s)
{
    int min = INT_MAX, min_index = s;
    if(!Dijkstra_called)
    {
        isColored = false;
        for(int i = 0; i < v.size();i++)
        {
            if(i == s) 
            {
                v[i].dist = 0;
            }
            else
            {
                v[i].dist = INT_MAX;
            }
        }
    }
    Dijkstra_called = true;
    doDijkstra = false;
    for(int i = 0;i < v.size();i++)
    {
        if(!v[i].visited && v[i].adj.size() != 0) doDijkstra = true;
    }
    if(!doDijkstra)
    {
        if(!isColored)
        {
            for(int i = 0; i < e.size(); i++)
            {
                if(e[i].visited) e[i].edge_surf = IMG_Load("images/edge_scanned.png");
                else e[i].edge_surf = IMG_Load("images/edge.png");
            }
            for(int i = 0; i < v.size(); i++) if(v[i].visited) v[i].vertex_surf = IMG_Load("images/vertex_scanned.png");
            isColored = true;
        }
      return;
    }
    for(int i = 0;i < v.size();i++)
    {
        string str;
        if(v[i].dist == INT_MAX) str = "inf" ;
        else str = std::to_string(v[i].dist);
        text_font2 = TTF_OpenFont("font/font.ttf",200);
        v[i].dist_surf = TTF_RenderText_Solid(text_font,str.c_str(),col2);
    }
    for(int i = 0; i < v.size(); i++) if(v[i].visited) v[i].vertex_surf = IMG_Load("images/vertex_scanned.png");
    for(int i = 0; i < v.size(); i++)
    {
        if((!v[i].visited) && (v[i].dist < min))
        {
            min_index = i;
            min = v[i].dist;
        }
    }
    v[min_index].visited = true;
    v[min_index].vertex_surf = IMG_Load("images/vertex_current.png");
    int curr_wt;
    for(auto i : v[min_index].adj)
    {
        int curr;
        if(!v[i].visited) v[i].vertex_surf = IMG_Load("images/vertex_current.png");
        for(int j = 0;j < e.size();j++)
        {
            if((e[j].v1 == i && e[j].v2 == min_index) || (e[j].v2 == i && e[j].v1 == min_index))
            {
                e[j].edge_surf = IMG_Load("images/edge_current.png");
                curr_wt = e[j].weight;
                curr = j;
                break;
            }
        }
        if(v[min_index].dist + curr_wt < v[i].dist)
        {
            e[curr].visited = true;
            v[i].dist = v[min_index].dist + curr_wt;
        }
    }
    SDL_Delay(1000);
}

void Graph::clearAlg()
{
    isColored  = true;
    Dijkstra_called = false;
    for(int i = 0; i < v.size();i++) 
    {
        v[i].vertex_surf = IMG_Load("images/vertex.png");
        v[i].visited = false;
    }
    for(int i = 0; i < e.size();i++) 
    {
        e[i].edge_surf = IMG_Load("images/edge.png");
        e[i].visited = false;
    }
    queue.clear();
    while(!Stack.empty()) Stack.pop();
}

void Graph::clearGraph()
{
    isColored  = true;
    Dijkstra_called = false;
    v.clear();
    e.clear();
}

void Graph::PrintGraph()
{
    for(int i = 0;i < v.size();i++)
    {
        for(auto j: v[i].adj)
            std::cout<<j<<" ";
        std::cout<<std::endl;
    }
    std::cout<<std::endl;
}
