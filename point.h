

class Point
{
  public:
    int X;
    int Y;
    bool fixation = false;

    
  Point(int _X, int _Y)
  {
    X = _X;
    Y = _Y;  
  }

  Point offset(Point point)
  {
    int newX = (point.X + X) % 8;
    int newY = (point.Y + Y) % 8;
    if (newX < 0)
    {
        newX += 8;  
    }
    if (newY < 0)
    {
        newY += 8;  
    }
    
    return Point(newX, newY);
  }

  bool Point::operator!=(Point& right) {
    return (X != right.X) || (Y != right.Y);
  }

   bool Point::operator==(Point& right) {
    return (X == right.X) && (Y == right.Y);
  }
  
  
  Point offset(int _X, int _Y)
  {
    return offset(Point(_X, _Y));
  }
};
