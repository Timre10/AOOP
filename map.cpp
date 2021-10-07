#include <iostream>
#include <string>
#include "astar.h"
#include "map.h"

using std::string;

    Map::Map(string Mapdata, int width, int height){
        Mapdatab=Mapdata;
        this->width= width;
        this->height= height;
        for(int i=0;i<Mapdatab.length();i++){
            if(Mapdatab[i]==' '){
                for(int j=i+1;j<Mapdatab.length();j++){
                    if(Mapdatab[i]==' '){
                        Mapdatab.erase(0,j+2);
                        j= Mapdatab.length();
                        i= Mapdatab.length();
                    }
                }
            }
        }
        Mapdatab.erase(remove(Mapdatab.begin(),Mapdatab.end(),' '),Mapdatab.end());

        generator.setWorldSize({width, height});
        generator.setDiagonalMovement(false);
        for(int i=0;i<height;i++){
            for(int j=0;j<width;j++){
                if(Mapdatab[j+i*width]=='x'){
                    generator.addCollision({j, height-i-1});
                }
            }
        }
    }

    string Map::algorythm(string data){
        int x,y;
        bool first=true;
        string laufstring="";
        for(int i=0;i<height;i++){
            for(int j=0;j<width;j++){
                if(data[j+i*width]=='!'){
                    x=j;
                    y=height-i-1;
                }
            }
        }
        auto path = generator.findPath({x, y},{0, height-1});
        for(auto& coordinate : path) {
            if(first==true){
                x= coordinate.x;
                y= coordinate.y;
                first= false;
            }else{
                if(x!=coordinate.x){
                    if((x-coordinate.x)==-1){
                        laufstring= laufstring+"r";
                    }else{
                        laufstring= laufstring+"l";
                    }

                }
                if(y!=coordinate.y){
                    if((y-coordinate.y)==-1){
                        laufstring= laufstring+"o";
                    }else{
                        laufstring= laufstring+"u";
                    }
                }
            }
            x= coordinate.x;
            y= coordinate.y;
        }
         return laufstring;
    }
