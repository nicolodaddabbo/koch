#ifndef LIBPSGRAPH_H
#define LIBPSGRAPH_H

typedef struct {
    double g_x, g_y, dir;
} Turtle;

/** Starts a new graph with given filename */
void start( const char *filename );

/** Ends the graph */
void end( void );

/** Draws a line of given length (in millimeters) */
void draw( double length );

/** Makes a move of given length (in millimeters), without drawing */
void move( double length );

/** Turns right of a given angle (in degrees) */
void turn( double ang );

/** Save the current position and direction into structure t */
void save_state(Turtle *t);

/** Restore previously saved position and direction from structure t */
void restore_state(const Turtle *t);

#endif
