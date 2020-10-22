#include<stdio.h>
#include<stdbool.h>
#include<math.h>
#include<graphics.h>


int mat_adj[4][4] = {	
                    0, 0, 0, 0,
                    0, 0, 0, 0,
                    0, 0, 0, 0,
                    0, 0, 0, 0
                    };
float mat_cord[4][2] = {
                    0, 9,
                    -4, 3,
                    4, 3,
                    0, 0
                    };
float portee=5;
bool different(float v[],float w[]){
    if(v[0]==w[0] && v[1]==w[1]){
        return false;
    }else{
        return true;
    }
}

bool distance_test_gg(float v[],float w[],float m[]){
    float D_mv,D_mw;
    float x,y;
    // distance (m,v)
    x = pow(v[0] - m[0],2);
	y = pow(v[1] - m[1],2);
	D_mv = sqrt(x + y);
    // distance (m,w)
    x = pow(w[0] - m[0],2);
	y = pow(w[1] - m[1],2);
    D_mw = sqrt(x + y);
    // tester si w est dans le cercle de diametre (u,v)
    if(D_mw <= D_mv){
        //printf("l'arrete s'enleve \n");
        return true; //l'arrete s'enleve
    }else{
        //printf("l'arrete reste \n");
        return false; //l'arrete reste
    }
}
void gg(){
    int i=0, j=0, k=0;
    float u[2], v[2], w[2], m[2];// les points
    for(i=0; i<4; i++){
        // fixé u 
        u[0] = mat_cord[i][0]; /// Xu
        u[1] = mat_cord[i][1]; /// Yu
        for(j=0; j<4; j++){
            v[0] = mat_cord[j][0]; /// Xv
            v[1] = mat_cord[j][1]; /// Yv
            if(mat_adj[i][j]==1 && different(u,v)){
                for(k=0; k<4; k++){
                    w[0] = mat_cord[k][0]; /// Xw
                    w[1] = mat_cord[k][1]; /// Yw
                    if(mat_adj[i][k]==1 && different(u,w) && different(v,w)){
                        //cordonnées de m
                        m[0] = (u[0] + v[0])/2; /// Xm
                        m[1] = (u[1] + v[1])/2; /// Ym
                        //calcule de distance et test
                        if(distance_test_gg(v,w,m)){
                            mat_adj[i][j]=0;
                            printf("deleted edge i=%d, j=%d, k=%d \n",i,j,k);
                        }
                    }
                }
            }
        }    
    }
}

float max(float a,float b){
    if(a >= b){
        return a;
    }else{
        return b;
    }
}
bool distance_test_rng(float u[],float v[],float w[]){
    float D_uw,D_vw,D_uv;
    float x,y;
    // distance (w,v)
    x = pow(w[0] - v[0],2);
	y = pow(w[1] - v[1],2);
	D_vw = sqrt(x + y);
    // distance (u,w)
    x = pow(w[0] - u[0],2);
	y = pow(w[1] - u[1],2);
    D_uw = sqrt(x + y);
    // distance (u,v)
    x = pow(v[0] - u[0],2);
	y = pow(v[1] - u[1],2);
    D_uv = sqrt(x + y);
    // tester si w est dans le cercle de diametre (u,v)
    if(D_uv >= max(D_vw,D_uw)){
        //printf("l'arrete s'enleve \n");
        return true; //l'arrete s'enleve
    }else{
        //printf("l'arrete reste \n");
        return false; //l'arrete reste
    }
}
void rng(){
    int i=0, j=0, k=0;
    float u[2], v[2], w[2];// les points
    for(i=0; i<4; i++){
        // fixé u 
        u[0] = mat_cord[i][0]; /// Xu
        u[1] = mat_cord[i][1]; /// Yu
        for(j=0; j<4; j++){
            v[0] = mat_cord[j][0]; /// Xv
            v[1] = mat_cord[j][1]; /// Yv
            if(mat_adj[i][j]==1 && different(u,v)){
                for(k=0; k<4; k++){
                    w[0] = mat_cord[k][0]; /// Xw
                    w[1] = mat_cord[k][1]; /// Yw
                    if(mat_adj[i][k]==1 && different(u,w) && different(v,w)){
                        //calcule de distance et test
                        if(distance_test_rng(u,v,w)){
                            mat_adj[i][j]=0;
                            printf("deleted edge i=%d, j=%d, k=%d \n",i,j,k);
                        }
                    }
                }
            }
        }    
    }
}

bool porte(float u[],float v[]){
	float D_uv,x,y;
	// distance (u,v)
    	x = pow(v[0] - u[0],2);
	y = pow(v[1] - u[1],2);
   	D_uv = sqrt(x + y);
	printf("D_uv : %f \n",D_uv);
	if(D_uv <= portee){
		return true;
	}else{
		return false;	
	}
}

void adj(){
	float u[2],v[2];
	for(int a=0;a<4;a++){
		for(int b=0;b<4;b++){
			u[0] = mat_cord[a][0]; /// Xu
       			u[1] = mat_cord[a][1]; /// Yu
			v[0] = mat_cord[b][0]; /// Xv
		        v[1] = mat_cord[b][1]; /// Yv
			if(porte(u,v) && different(u,v)){
				printf(" i=%d, j=%d \n\n", a,b);
				mat_adj[a][b]=1;
			}
		}
	}
	
}
void draw(){
    int gd = DETECT, gm;
 
   initgraph(&gd, &gm, "C:\\TC\\BGI");
   
    for(int l=0; l<4; l++){
        for(int h=0; h<4; h++){
            if(mat_adj[l][h] == 1 ){
                line(mat_cord[l][0]*10+50, mat_cord[h][0]*10+50, mat_cord[l][1]*10+50, mat_cord[l][1]*10+50);
            }
        }
    }
   
   
}
void main(){
    int choix;
	

    adj();


    printf("voulais vous utiliser ?(entrez le numéro de l'algorithme)\n");
    printf("1-GG \n2-RNG\n");
    scanf("%d",&choix);

    switch(choix){
        case 1:
            gg();
            break;
        case 2:
            rng();
            break;   
        default:
            printf("error 404");
            break;
    }


    for(int l=0; l<4; l++){
        for(int h=0; h<4; h++){
            printf("%d ,",mat_adj[l][h]);
        }
        printf("\n");
    }
    draw();
    getch();
   closegraph();
}
