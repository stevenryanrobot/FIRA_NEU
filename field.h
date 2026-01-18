#ifndef _FIELD_HEADER
#define _FIELD_HEADER

#include "geometric.h"


class Field {
public:
    Field();
    ~Field();
    static const double height;
    static const double width;
    static const double goalDepth;
    static const double goalWidth;
    static const double penaltyAheight;
    static const double penaltyAwidth;
    static const double penaltyBheight;
	static const double penaltyBwidth;
    static const double penaltyPoint;
    static const double penaltyCheight;
    static const double penaltyCwidth;
    static const double FBHeightOffSet;
    static const double FBHWidthOffSet;
    static const double markerFBOffSet;
    static const double centerCircleRadius;
    static const double cornerTriangleSide;
	static const double pushingWidth;
    static rcsc::Vector2D corner1() { return rcsc::Vector2D(2.4, 170.6); }
    static rcsc::Vector2D corner2() { return rcsc::Vector2D(9.4, 177.6); }
    static rcsc::Vector2D corner3() { return rcsc::Vector2D(210.6, 177.6); }
    static rcsc::Vector2D corner4() { return rcsc::Vector2D(217.6, 170.6); }
    static rcsc::Vector2D corner5() { return rcsc::Vector2D(217.6, 9.4); }
    static rcsc::Vector2D corner6() { return rcsc::Vector2D(210.6, 2.4); }
    static rcsc::Vector2D corner7() { return rcsc::Vector2D(9.4, 2.4); }
    static rcsc::Vector2D corner8() { return rcsc::Vector2D(2.4, 9.4); }
    static rcsc::Vector2D FBLeftTop()  { return rcsc::Vector2D(FBHWidthOffSet, height/2 - FBHeightOffSet);}
    static rcsc::Vector2D FBRightTop() { return rcsc::Vector2D(width - FBHWidthOffSet, height- FBHeightOffSet);}
    static rcsc::Vector2D FBLeftBot()  { return rcsc::Vector2D( FBHWidthOffSet,   FBHeightOffSet);}
    static rcsc::Vector2D FBRightBot() { return rcsc::Vector2D(width - FBHWidthOffSet,FBHeightOffSet);}

    static rcsc::Vector2D cornerLeftTop()  { return rcsc::Vector2D(0, height);}
    static rcsc::Vector2D cornerLeftBot()  { return rcsc::Vector2D(0, 0);}
    static rcsc::Vector2D cornerRightTop() { return rcsc::Vector2D(width, height);}
    static rcsc::Vector2D cornerRightBot() { return rcsc::Vector2D(width, 0);}

    static rcsc::Vector2D ourGoal()  { return rcsc::Vector2D(width,   height/2); }
    static rcsc::Vector2D ourGoalT() { return rcsc::Vector2D(width, height / 2 +30); }
    static rcsc::Vector2D ourGoalB() { return rcsc::Vector2D(width, height / 2- 30); }
    static rcsc::Vector2D oppGoal()  { return rcsc::Vector2D( 0, height / 2); }
    static rcsc::Vector2D oppGoalT() { return rcsc::Vector2D(0, height / 2 +20); }
    static rcsc::Vector2D oppGoalB() { return rcsc::Vector2D( 0, height / 2-20); }

    static rcsc::Vector2D ourPenalty() { return rcsc::Vector2D( width - penaltyPoint, 0); }
    static rcsc::Vector2D oppPenalty() { return rcsc::Vector2D( 0 + penaltyPoint, 0); }

    static rcsc::Rect2D ourGoalRect()     { return rcsc::Rect2D( width, goalWidth/2-height/2, goalWidth, goalDepth);}
    static rcsc::Rect2D ourPenaltyARect() { return rcsc::Rect2D(width- penaltyAwidth, -penaltyAheight/2+height/2, penaltyAwidth, penaltyAheight);}
    static rcsc::Rect2D ourPenaltyBRect() { return rcsc::Rect2D(width - penaltyBwidth, -penaltyBheight / 2 + height / 2, penaltyBwidth, penaltyBheight);}
    static rcsc::Rect2D ourPenaltyCRect() { return rcsc::Rect2D(width-penaltyCwidth, height/2-penaltyCheight/2, penaltyCwidth, penaltyCheight);}

    static rcsc::Rect2D oppGoalRect()     { return rcsc::Rect2D(-goalWidth, height/2-goalWidth/2, goalWidth, goalDepth);}
    static rcsc::Rect2D oppPenaltyARect() { return rcsc::Rect2D(0, height/2-penaltyAheight/2, penaltyAwidth, penaltyAheight);}
    static rcsc::Rect2D oppPenaltyBRect() { return rcsc::Rect2D(0, height/2-penaltyBheight/2, penaltyBwidth, penaltyBheight);}
    static rcsc::Rect2D oppPenaltyCRect() { return rcsc::Rect2D(0, height/2-penaltyCheight/2, penaltyCwidth, penaltyCheight);}

    static rcsc::Rect2D fieldRect()     { return rcsc::Rect2D(0,0, width, height);}
	static rcsc::Rect2D SafeFieldRect() { return rcsc::Rect2D( width  - 10, height- 10, width - 10, height - 10); }
    static rcsc::Rect2D ourHalfRect()   { return rcsc::Rect2D(width/2, 0, width/2, height);}
    static rcsc::Rect2D oppHalfRect()   { return rcsc::Rect2D(0, 0, width/2, height);}
	static bool isInPushingArea(const rcsc::Vector2D& v) { return !SafeFieldRect().contains(v); }
    static rcsc::Triangle2D oppTopTriangle() { return rcsc::Triangle2D(rcsc::Vector2D(3, 177), rcsc::Vector2D(3, 170), rcsc::Vector2D(10, 177)); }
    static rcsc::Triangle2D oppBottomTriangle() { return rcsc::Triangle2D(rcsc::Vector2D(3, 10), rcsc::Vector2D(3, 3), rcsc::Vector2D(10, 3)); }
    static rcsc::Triangle2D ourTopTriangle() { return rcsc::Triangle2D(rcsc::Vector2D(217, 177), rcsc::Vector2D(217, 170), rcsc::Vector2D(210, 177)); }
    static rcsc::Triangle2D ourBottomTriangle() { return rcsc::Triangle2D(rcsc::Vector2D(210, 3), rcsc::Vector2D(217, 3), rcsc::Vector2D(217, 10)); }

    //bounds for ball
    static rcsc::Line2D L_Leftforball() { return rcsc::Line2D(corner1(), corner8()); }
    static rcsc::Line2D L_Rightforball() { return rcsc::Line2D(corner4(), corner5()); }
    static rcsc::Line2D L_Topforball() { return rcsc::Line2D(corner2(), corner3()); }
    static rcsc::Line2D L_Bottomforball() { return rcsc::Line2D(corner6(), corner7()); }
    static rcsc::Line2D L_LTforball() { return rcsc::Line2D(corner1(), corner2()); }
    static rcsc::Line2D L_LBforball() { return rcsc::Line2D(corner7(), corner8()); }
    static rcsc::Line2D L_RTforball() { return rcsc::Line2D(corner3(), corner4()); }
    static rcsc::Line2D L_RBforball() { return rcsc::Line2D(corner5(), corner6()); }
    static rcsc::Segment2D Leftforball() { return rcsc::Segment2D(corner1(),corner8()); }
    static rcsc::Segment2D Rightforball() { return rcsc::Segment2D(corner4(), corner5()); }
    static rcsc::Segment2D Topforball() { return rcsc::Segment2D(corner2(), corner3()); }
    static rcsc::Segment2D Bottomforball() { return rcsc::Segment2D(corner6(), corner7()); }
    static rcsc::Segment2D LTforball() { return rcsc::Segment2D(corner1(), corner2()); }
    static rcsc::Segment2D LBforball() { return rcsc::Segment2D(corner7(), corner8()); }
    static rcsc::Segment2D RTforball() { return rcsc::Segment2D(corner3(), corner4()); }
    static rcsc::Segment2D RBforball() { return rcsc::Segment2D(corner5(), corner6()); }
    static rcsc::Vector2D Boundintersction(rcsc::Segment2D L);
    static bool Boundintersctionexist(rcsc::Segment2D L);
    static bool OurGoalinterexist(rcsc::Segment2D balltrack);
    static rcsc::Vector2D OurGoalinter(rcsc::Segment2D balltrack);
    static bool OurPenaltyinterexist(rcsc::Segment2D balltrack);
    static rcsc::Vector2D OurPenaltyinter(rcsc::Segment2D balltrack);
    static bool OppPenaltyinterexist(rcsc::Segment2D balltrack);
    static rcsc::Vector2D OppPenaltyinter(rcsc::Segment2D balltrack);
    static bool OppGoalinterexist(rcsc::Segment2D balltrack);
    static rcsc::Vector2D OppGoalinter(rcsc::Segment2D balltrack);
    static bool InFobidenBound(rcsc::Vector2D pos);

};

#endif // _FIELD_HEADER