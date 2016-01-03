// Gmsh
// Tips and notes:
// If you get an error when defining a physical volume, be sure that it is not 
// the last line and no line breaks after it. Putting a few line breaks at the 
// end will rectify the issue.


// Rotation of entities.
Rotate{ {0,0,1}, {top_left_corner[0],top_left_corner[1],0}, 
  tilt }
{
  Line{lns[]};
}

// 2D extrusion
new_entities[] = 
Extrude{0,0,cell_depth}
{
  Surface{extrude_surface};
  Layers{1};
  Recombine;
};

Function draw_rectangle
  // the outline of the rectangle is output from this function.
  // In: top_left_corner[] = {}; lc = ; W = ; H = ;
  pts[] = {};
  Point(ce++) = {top_left_corner[0], top_left_corner[1], 0, lc}; 
  pts[]+=ce;
  Point(ce++) = {top_left_corner[0], top_left_corner[1]-H, 0, lc};
  pts[]+=ce;
  Point(ce++) = {top_left_corner[0]+W, top_left_corner[1]-H, 0, lc};
  pts[]+=ce;
  Point(ce++) = {top_left_corner[0]+W, top_left_corner[1], 0, lc};
  pts[]+=ce;
  lns[] = {};
  Line(ce++) = {pts[0], pts[1]}; lns[]+=ce;
  Line(ce++) = {pts[1], pts[2]}; lns[]+=ce;
  Line(ce++) = {pts[2], pts[3]}; lns[]+=ce;
  Line(ce++) = {pts[3], pts[0]}; lns[]+=ce;
Return

Function rotate_lines
  // In: lns[] = {}; rotation_center[] = {}; rotation = ;
  If ( rotation > 0 )
    Rotate{ {0,0,1}, { rotation_center[0], rotation_center[1], 0 }, rotation }
    {
      Line{lns[]};
    }
  EndIf
Return













/*
Acronyms:
  LE: leading edge
  AOA: angle of attack
*/

Function calculate_quarter_chord
  /*
  Gives dx and dy such that the quarter chord position is at 0,0.
  Assumes we are starting with a 0-AOA chord line. 
  Inputs:
    target_aoa: the AOA of the chord line of the airfoil.
    target_chord: chord length. 
  Outputs:
    dx, dy: LE displacement to get the desired quarter-chord placement. 
  */
  dx = -0.25*target_chord*Cos(target_aoa);
  dy = 0.25*target_chord*Sin(target_aoa);
Return