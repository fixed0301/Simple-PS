#include<iostream>
 
using namespace std;
 
int map[12][12];
int idx = 0;
int x_idx[144];
int y_idx[144];
int rst;
int length;
 
int check_solve(int x_point, int y_point, int N, int tmp_map[12][12], int dx, int dy){
    x_point += dx;
    y_point += dy;
    int cnt = 0;
 
    while( x_point >= 0 && y_point >= 0 && x_point < N && y_point < N){
        if(tmp_map[x_point][y_point] == 0){
            x_point += dx;
            y_point += dy;
            ++cnt;
        }else{
            return -1;
        }
    }
    return cnt;
}
int solve(int idx, int max_idx, int N, int tmp_map[12][12], int tmp_rst, int tmp_length){
    int cur_map[12][12];
    int matrix[4][2]={{-1,0}, {0,-1}, {1,0}, {0,1}};
    int dx;
    int dy;
    int x_point;
    int y_point;
 
 
    if(idx == max_idx){
        if(tmp_rst > rst ){
            rst = tmp_rst;
            length = tmp_length;
        }else if( tmp_rst == rst && tmp_length < length){
            length = tmp_length;
        }
        return 0;
    }

    x_point = x_idx[idx];
    y_point = y_idx[idx];
    if(x_point == 0 || x_point == N-1 || y_point == 0 || y_point == N-1){
        solve(idx+1,max_idx, N, tmp_map, tmp_rst+1, tmp_length);
    } else {
        for(int i = 0; i < 4; ++i){
            for(int i = 0; i < N; ++i){
                for(int j = 0; j < N; ++j){
                    cur_map[i][j] = tmp_map[i][j];
                }
            }
            dx = matrix[i][0];
            dy = matrix[i][1];
 
            int cur_rst = check_solve(x_point, y_point, N, tmp_map, dx, dy);
            if(cur_rst != -1){
 
                while( x_point >= 0 && y_point >= 0 && x_point < N && y_point < N){
                    cur_map[x_point][y_point]=2;
                    x_point += dx;
                    y_point += dy;
                }
                solve(idx+1,max_idx, N, cur_map, tmp_rst+1, tmp_length + cur_rst);
                x_point = x_idx[idx];
                y_point = y_idx[idx];
            }
        }
        solve(idx+1,max_idx, N, tmp_map, tmp_rst, tmp_length);
    }
    return 0;
}
int main(int argc, char** argv)
{
    int test_case;
    int T;
   
    cin>>T;
    
    for(test_case = 1; test_case <= T; ++test_case)
    {
 
        /////////////////////////////////////////////////////////////////////////////////////////////
        /*
            대충 구현
         */
        /////////////////////////////////////////////////////////////////////////////////////////////
 
        int N;
        cin >> N;
        idx = 0;
        rst = 0;
        length = 9999999;
 
        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < N; ++j){
                cin >> map[i][j];
                if(map[i][j] == 1){
                    x_idx[idx] = i;
                    y_idx[idx] = j;
                    ++idx;
                }
            }
        }
 
        solve(0,idx,N,map,0,0);
        cout << "#" << test_case << " " << length << endl;
 
    }
    return 0;
}

