class Point:
    def __init__(self,x:float,y:float):
        self.x=x
        self.y=y    
class Circle:
    def __init__(self, center:Point,radius:float):
        self.center=center
        self.radius=radius
class Rectangle:
    def __init__(self,w:Point,x:Point,y:Point,z:Point):
        self.w=w
        self.x=x
        self.y=y
        self.z=z
def point_in_circle(C:Circle,P:Point):
    d=(((P.x-C.center.x)**2)+((P.y-C.center.y)**2))**.5
    if d<=C.radius:
        return True
def rect_in_circle(C:Circle,R:Rectangle):
    x0=point_in_circle(C,R.w)
    x1=point_in_circle(C,R.x)
    x2=point_in_circle(C,R.y)
    x3=point_in_circle(C,R.z)
    if x0==True and x1==True and x2==True and x3==True:
        return True
def rect_circle_overlap1(C:Circle,R:Rectangle):
    x0=point_in_circle(C,R.w)
    x1=point_in_circle(C,R.x)
    x2=point_in_circle(C,R.y)
    x3=point_in_circle(C,R.z)
    if x0==True or x1==True or x2==True or x3==True:
        return True
def rect_circle_overlap2(C:Circle,R:Rectangle):
    xbound={R.w.x,R.x.x,R.y.x,R.z.x}
    xbound=list(xbound)
    if xbound[0]>xbound[1]:
        x0=xbound[1]
        x1=xbound[0]
    else:
        x0=xbound[0]
        x1=xbound[1]
    ybound={R.w.y,R.x.y,R.y.y,R.z.y}
    ybound=list(ybound)
    if ybound[0]>ybound[1]:
        y0=ybound[1]
        y1=ybound[0]
    else:
        y0=ybound[0]
        y1=ybound[1]
    lx=list()
    for x in range(x1-x0):
        lx.append(x0+x)
    lx.append(x1)
    ly=list()
    for y in range(y1-y0):
        ly.append(y0+y)
    ly.append(y1)
    for x in lx:
        for y in ly:
            d=point_in_circle(C,Point(x,y))
            if d==True:
                return True
C=Circle(Point(150,100),75)




def test_point_in_circle(C,P):
    print('the result of point_in_circle is:')
    x=point_in_circle(C,P)
    print(x)
def test_rect_in_circle(C,R):
    print('the result of rect_in_circle is:')
    x=rect_in_circle(C,R)
    print(x)
def test_rect_circle_overlap1(C,R):
    print('the result of rect_circle_overlap1 is:')
    x=rect_circle_overlap1(C,R)
    print(x)
def test_rect_circle_overlap2(C,R):
    print('the result of rect_circle_overlap2 is:')
    x=rect_circle_overlap2(C,R)
    print(x)
if __name__ == '__main__':
    test_point_in_circle(int(input('Circle:')),int(input('Point:')))
    test_rect_in_circle(int(input('Circle:')),int(input('Rectangle:')))
    test_rect_circle_overlap1(int(input('Circle:')),int(input('Rectangle:')))
    test_rect_circle_overlap2(int(input('Circle:')),int(input('Rectangle:')))