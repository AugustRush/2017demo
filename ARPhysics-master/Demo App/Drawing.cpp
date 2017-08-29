//
//  Drawing.c
//
//  Created by Adrian Russell on 17/02/2013.
//  Copyright (c) 2013 Adrian Russell. All rights reserved.
//
//  THIS DRAWING IS BASED ON THE DRAWING FROM THE CHIPMUNK PHYSICS ENGINE BY SCOTT LEMBCKE (his copyright below)

/* Copyright (c) 2007 Scott Lembcke
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "Drawing.h"
#include "OpenGL/gl.h"
#include "OpenGL/glu.h"
#include <GLUT/glut.h>
#include <string.h>
#include "PolygonBody.h"
#include "CircleBody.h"





Color randomColor()
{
    float r = 0.3;
    float g = 0.3;
    float b = 0.3;
    return (Color){r, g, b, 1.0};
}


//static const GLfloat pillVAR[] = {
//    0.0000f,  1.0000f, 1.0f,
//    0.2588f,  0.9659f, 1.0f,
//    0.5000f,  0.8660f, 1.0f,
//    0.7071f,  0.7071f, 1.0f,
//    0.8660f,  0.5000f, 1.0f,
//    0.9659f,  0.2588f, 1.0f,
//    1.0000f,  0.0000f, 1.0f,
//    0.9659f, -0.2588f, 1.0f,
//    0.8660f, -0.5000f, 1.0f,
//    0.7071f, -0.7071f, 1.0f,
//    0.5000f, -0.8660f, 1.0f,
//    0.2588f, -0.9659f, 1.0f,
//    0.0000f, -1.0000f, 1.0f,
//    
//    0.0000f, -1.0000f, 0.0f,
//	-0.2588f, -0.9659f, 0.0f,
//	-0.5000f, -0.8660f, 0.0f,
//	-0.7071f, -0.7071f, 0.0f,
//	-0.8660f, -0.5000f, 0.0f,
//	-0.9659f, -0.2588f, 0.0f,
//	-1.0000f, -0.0000f, 0.0f,
//	-0.9659f,  0.2588f, 0.0f,
//	-0.8660f,  0.5000f, 0.0f,
//	-0.7071f,  0.7071f, 0.0f,
//	-0.5000f,  0.8660f, 0.0f,
//	-0.2588f,  0.9659f, 0.0f,
//    0.0000f,  1.0000f, 0.0f,
//};
//static const int pillVAR_count = sizeof(pillVAR)/sizeof(GLfloat)/3;

static const GLfloat circleVAR[] = {
    0.0000f,  1.0000f,
    0.2588f,  0.9659f,
    0.5000f,  0.8660f,
    0.7071f,  0.7071f,
    0.8660f,  0.5000f,
    0.9659f,  0.2588f,
    1.0000f,  0.0000f,
    0.9659f, -0.2588f,
    0.8660f, -0.5000f,
    0.7071f, -0.7071f,
    0.5000f, -0.8660f,
    0.2588f, -0.9659f,
    0.0000f, -1.0000f,
	-0.2588f, -0.9659f,
	-0.5000f, -0.8660f,
	-0.7071f, -0.7071f,
	-0.8660f, -0.5000f,
	-0.9659f, -0.2588f,
	-1.0000f, -0.0000f,
	-0.9659f,  0.2588f,
	-0.8660f,  0.5000f,
	-0.7071f,  0.7071f,
	-0.5000f,  0.8660f,
	-0.2588f,  0.9659f,
    0.0000f,  1.0000f,
    0.0f, 0.0f, // For an extra line to see the rotation.
};
static const int circleVAR_count = sizeof(circleVAR)/sizeof(GLfloat)/2;

static inline void glColor_from_color(Color color)
{
	glColor4fv((GLfloat *)&color);
}

void drawCircle(Vector2 center, float radius, float rotation, Color fillColor, Color strokeColor)
{
    glVertexPointer(2, GL_FLOAT, 0, circleVAR);
    
	glPushMatrix();
    {
		glTranslatef(center.x, center.y, 0.0f);
		glRotatef(rotation * (180.0f / M_PI), 0.0f, 0.0f, 1.0f);
		glScalef(radius, radius, 1.0f);
		
		if(fillColor.a > 0){
			glColor_from_color(fillColor);
			glDrawArrays(GL_TRIANGLE_FAN, 0, circleVAR_count);
		}
		
        
		if(strokeColor.a > 0){
			glColor_from_color(strokeColor);
			glDrawArrays(GL_LINE_STRIP, 0, circleVAR_count);
		}
	}
    glPopMatrix();
}

void drawRect(Rect rect, float rotation, Color fillColor, Color strokeColor)
{
    Vector2 center = rect.center();
    GLfloat points[10] = { rect.origin().x - center.x,                rect.origin().y - center.y,
                           rect.origin().x + rect.width() - center.x, rect.origin().y - center.y,
                           rect.origin().x + rect.width() - center.x, rect.origin().y + rect.height() - center.y,
                           rect.origin().x - center.x,                rect.origin().y + rect.height() - center.y,
                           rect.origin().x - center.x,                rect.origin().y - center.y};
    
    glVertexPointer(2, GL_FLOAT, 0, points);
    
    glPushMatrix();
    {
		glTranslatef(center.x, center.y, 0.0f);
		glRotatef(rotation * (180.0f / M_PI), 0.0f, 0.0f, 1.0f);
		//glScalef(radius, radius, 1.0f);
		
		if(fillColor.a > 0){
			glColor_from_color(fillColor);
			glDrawArrays(GL_TRIANGLE_FAN, 0, 5);
		}
		
        
		if(strokeColor.a > 0){
			glColor_from_color(strokeColor);
			glDrawArrays(GL_LINE_STRIP, 0, 5);
		}
	}
    glPopMatrix();
}

void drawPolygon(const Vector2* points, unsigned int pointCount, Vector2 center, float rotation, Color fillColor, Color strokeColor)
{
    glVertexPointer(2, GL_FLOAT, 0, points);
	
    glPushMatrix();
    {
        glTranslatef(center.x, center.y, 0.0f);
		glRotatef(rotation * (180.0f / M_PI), 0.0f, 0.0f, 1.0f);
		//glScalef(50.0, 50.0, 1.0f);
        
        if(fillColor.a > 0) {
            glColor_from_color(fillColor);
            glDrawArrays(GL_TRIANGLE_FAN, 0, pointCount);
        }
        
        if(strokeColor.a > 0) {
            glColor_from_color(strokeColor);
            glDrawArrays(GL_LINE_LOOP, 0, pointCount);
        }
    }
    glPopMatrix();
}



void drawLine(Vector2 a, Vector2 b, Color color)
{

    GLfloat verts[] = { a.x, a.y,
                        b.x, b.y, };
    
    glVertexPointer(2, GL_FLOAT, 0, verts);
    
	glColor_from_color(color);
	glDrawArrays(GL_LINES, 0, 2);
}


//void drawCapsule(Vector2 a, Vector2 b, float radius, Color fillColor, Color strokeColor)
//{
//    if(radius) {
//		glVertexPointer(3, GL_FLOAT, 0, pillVAR);
//		glPushMatrix(); {
//			Vector2 d = b - a;
//			Vector2 r = d * (radius / d.length());
//            
//#if USES_DOUBLES
//            GLdouble
//#else
//            GLfloat
//#endif
//			matrix[] = {
//                r.x, r.y, 0.0f, 0.0f,
//				-r.y, r.x, 0.0f, 0.0f,
//                d.x, d.y, 0.0f, 0.0f,
//                a.x, a.y, 0.0f, 1.0f,
//			};
//#if USES_DOUBLES
//			glMultMatrixd(matrix);
//#else
//            glMultMatrixf(matrix);
//#endif
//            
//			
//			if(fillColor.a > 0){
//				glColor_from_color(fillColor);
//				glDrawArrays(GL_TRIANGLE_FAN, 0, pillVAR_count);
//			}
//			
//			if(strokeColor.a > 0){
//				glColor_from_color(strokeColor);
//				glDrawArrays(GL_LINE_LOOP, 0, pillVAR_count);
//			}
//		} glPopMatrix();
//	} else {
//		drawLine(a, b, strokeColor);
//	}
//}

void drawString(int x, int y, const char *str)
{
	glColor3f(1.0f, 1.0f, 1.0f);
	glRasterPos2i(x, y);
	
    int len = (int)strlen(str);
	for(int i = 0; i < len; i++) {
		if(str[i] == '\n'){
			y -= 16;
			glRasterPos2i(x, y);
		} else {
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, str[i]);
		}
	}
}




void drawPolygonBody(PolygonBody *polygon, Color fillColor, Color strokeColor, bool drawAABB, Color aabbColor)
{
    drawPolygon(&(polygon->vertices()[0]), polygon->vertexCount(), polygon->position(), polygon->rotation(), fillColor, strokeColor);
    
    if (drawAABB) {
        drawRect(polygon->AABB(), 0.0, kNoColor, aabbColor);
    }
}


void drawCircleBody(CircleBody *circle, Color fillColor, Color strokeColor, bool drawAABB, Color aabbColor)
{
    drawCircle(circle->position(), circle->radius(), circle->rotation(), fillColor, strokeColor);
    
    if (drawAABB) {
        drawRect(circle->AABB(), 0.0, kNoColor, aabbColor);
    }
    
}



