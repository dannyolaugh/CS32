
class Coord  //i need this

{
public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
    Coord* ptr = new Coord(sr,sc);
    if(ptr->r() == er && ptr->c() == ec)
        return true;
    maze[ptr->r()][ptr->c()] = 'X';
    if(maze[ptr->r()-1][ptr->c()] == '.')
    {
        if(pathExists(maze, nRows, nCols, sr-1, sc, er, ec))
            return true;
    }
    
    if(maze[ptr->r()][ptr->c()+1] == '.')
    {
        if(pathExists(maze, nRows, nCols, sr, sc+1, er, ec))
            return true;
    }
    if(maze[ptr->r()+1][ptr->c()] == '.')
    {
        if(pathExists(maze, nRows, nCols, sr+1, sc, er, ec))
            return true;
    }
    if(maze[ptr->r()][ptr->c()-1] == '.')
    {
        if(pathExists(maze, nRows, nCols, sr, sc-1, er, ec))
            return true;
    }
    
    return false;
    
    
}
