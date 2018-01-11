<?php
/* ************************************************************************** */
/*                                                                            */
/*                 main_03.php for J06                                        */
/*                 Created on : Mon Mar 31 17:37:41 2014                      */
/*                 Made by : David "Thor" GIRON <thor@42.fr>                  */
/*                                                                            */
/* ************************************************************************** */


require_once 'Vertex.class.php';
require_once 'Vector.class.php';
require_once 'Matrix.class.php';


Vertex::$verbose = False;
Vector::$verbose = False;

//print( Matrix::doc() );
Matrix::$verbose = True;

print( 'Let\'s start with an harmless identity matrix :' . PHP_EOL );
$I = new Matrix( array( 'preset' => Matrix::IDENTITY ) );
print( $I . PHP_EOL . PHP_EOL );

print( 'So far, so good. Let\'s create a translation matrix now.' . PHP_EOL );
$vtx = new Vertex( array( 'x' => 20.0, 'y' => 20.0, 'z' => 0.0 ) );
$vtc = new Vector( array( 'dest' => $vtx ) );
$T  = new Matrix( array( 'preset' => Matrix::TRANSLATION, 'vtc' => $vtc ) );
print( $T . PHP_EOL . PHP_EOL );

print( 'A scale matrix is no big deal.' . PHP_EOL );
$S  = new Matrix( array( 'preset' => Matrix::SCALE, 'scale' => 10.0 ) );
print( $S . PHP_EOL . PHP_EOL );

print( 'A Rotation along the OX axis :' . PHP_EOL );
$RX = new Matrix( array( 'preset' => Matrix::RX, 'angle' => M_PI_4 ) );
print( $RX . PHP_EOL . PHP_EOL );

print( 'Or along the OY axis :' . PHP_EOL );
$RY = new Matrix( array( 'preset' => Matrix::RY, 'angle' => M_PI_2 ) );
print( $RY . PHP_EOL . PHP_EOL );

print( 'Do a barrel roll !' . PHP_EOL );
$RZ = new Matrix( array( 'preset' => Matrix::RZ, 'angle' => 2 * M_PI ) );
print( $RZ . PHP_EOL . PHP_EOL );

print( 'The bad guy now, the projection matrix : 3D to 2D !' . PHP_EOL );
print( 'The values are arbitray. We\'ll decipher them in the next exercice.' . PHP_EOL );
$P = new Matrix( array( 'preset' => Matrix::PROJECTION,
						'fov' => 60,
						'ratio' => 640/480,
						'near' => 1.0,
						'far' => -50.0 ) );
print( $P . PHP_EOL . PHP_EOL );

print( 'Matrices are so awesome, that they can be combined !' . PHP_EOL );
print( 'This is a model matrix that scales, then rotates around OY axis,' . PHP_EOL );
print( 'then rotates around OX axis and finally translates.' . PHP_EOL );
print( 'Please note the reverse operations order. It\'s not an error.' . PHP_EOL );
$M = $T->mult( $RX )->mult( $RY )->mult( $S );
print( $M . PHP_EOL . PHP_EOL );

print( 'What can you do with a matrix and a vertex ?' . PHP_EOL );
$vtxA = new Vertex( array( 'x' => 1.0, 'y' => 1.0, 'z' => 0.0 ) );
print( $vtxA . PHP_EOL );
print( $M . PHP_EOL );
print( 'Transform the damn vertex !' . PHP_EOL );
$vtxB = $M->transformVertex( $vtxA );
print( $vtxB . PHP_EOL . PHP_EOL );

?>
