
// The sample model.  You should build a file
// very similar to this for when you make your model.

#include "modelerview.h"
#include "modelerapp.h"
#include "modelerdraw.h"
#include <FL/gl.h>

#include "modelerglobals.h"

#include "stb_image.h"


// Texture loading, reference: https://learnopengl.com/. Really helped me out!

void texture_alloc(char* fname)
{
	int width, height, nrChannels;

	unsigned char* data = stbi_load(fname, &width, &height, &nrChannels, 0);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB,
		GL_UNSIGNED_BYTE, data);



	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);



	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_MODULATE);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
}

void drawPyramid(double x1, double y1, double z1,
	double x2, double y2, double z2,
	double x3, double y3, double z3,
	double x4, double y4, double z4) {
	drawTriangle(x1, y1, z1, x2, y2, z2, x3, y3, z3);
	drawTriangle(x1, y1, z1, x2, y2, z2, x4, y4, z4);
	drawTriangle(x1, y1, z1, x3, y3, z3, x4, y4, z4);
	drawTriangle(x2, y2, z2, x3, y3, z3, x4, y4, z4);
}
// To make a SampleModel, we inherit off of ModelerView
class SampleModel : public ModelerView
{
public:
	SampleModel(int x, int y, int w, int h, char* label)
		: ModelerView(x, y, w, h, label) { }

	virtual void draw();
};

// We need to make a creator function, mostly because of
// nasty API stuff that we'd rather stay away from.
ModelerView* createSampleModel(int x, int y, int w, int h, char* label)
{
	return new SampleModel(x, y, w, h, label);
}

// Texture loading, reference: https://learnopengl.com/. Really helped me out!
void drawTexture(double x, double y, double z)
{
	ModelerDrawState* mds = ModelerDrawState::Instance();


	/* remember which matrix mode OpenGL was in. */
	int savemode;
	glGetIntegerv(GL_MATRIX_MODE, &savemode);

	/* switch to the model matrix and scale by x,y,z. */
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glScaled(x, y, z);


	glEnable(GL_TEXTURE_2D);

	int width, height, nrChannels;

	unsigned char* data = stbi_load("Durandal.jpg", &width, &height, &nrChannels, 0);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB,
		GL_UNSIGNED_BYTE, data);

	stbi_image_free(data);

	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);



	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_MODULATE);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	glBegin(GL_QUADS);

	glNormal3d(0.0, 0.0, -1.0);
	glTexCoord2f(0.0, 1.0); glVertex3d(0.0, 0.0, 0.0);
	glTexCoord2f(0.0, 0.0); glVertex3d(0.0, 1.0, 0.0);
	glTexCoord2f(1.0, 0.0); glVertex3d(1.0, 1.0, 0.0);
	glTexCoord2f(1.0, 1.0); glVertex3d(1.0, 0.0, 0.0);

	glNormal3d(0.0, -1.0, 0.0);
	glVertex3d(0.0, 0.0, 0.0); glVertex3d(1.0, 0.0, 0.0);
	glVertex3d(1.0, 0.0, 1.0); glVertex3d(0.0, 0.0, 1.0);

	glNormal3d(-1.0, 0.0, 0.0);
	glVertex3d(0.0, 0.0, 0.0); glVertex3d(0.0, 0.0, 1.0);
	glVertex3d(0.0, 1.0, 1.0); glVertex3d(0.0, 1.0, 0.0);

	glNormal3d(0.0, 0.0, 1.0);
	glVertex3d(0.0, 0.0, 1.0); glVertex3d(1.0, 0.0, 1.0);
	glVertex3d(1.0, 1.0, 1.0); glVertex3d(0.0, 1.0, 1.0);

	glNormal3d(0.0, 1.0, 0.0);
	glVertex3d(0.0, 1.0, 0.0); glVertex3d(0.0, 1.0, 1.0);
	glVertex3d(1.0, 1.0, 1.0); glVertex3d(1.0, 1.0, 0.0);

	glNormal3d(1.0, 0.0, 0.0);
	glVertex3d(1.0, 0.0, 0.0); glVertex3d(1.0, 1.0, 0.0);
	glVertex3d(1.0, 1.0, 1.0); glVertex3d(1.0, 0.0, 1.0);


	glEnd();
	glDisable(GL_TEXTURE_2D);
	/* restore the model matrix stack, and switch back to the matrix
	mode we were in. */
	glPopMatrix();
	glMatrixMode(savemode);

}

// We are going to override (is that the right word?) the draw()
// method of ModelerView to draw out SampleModel
void SampleModel::draw()
{
	// This call takes care of a lot of the nasty projection 
	// matrix stuff.  Unless you want to fudge directly with the 
	// projection matrix, don't bother with this ...
	ModelerView::draw();
	float bodyx = 1;
	float bodyy = 1.5;
	float bodyz = 0.5;
	float headr = bodyx * 3 / 8;
	float armx = bodyx / 4;
	float army = bodyy / 3;
	float armz = bodyz / 2;
	float forearmx = bodyx / 4;
	float forearmy = bodyy / 3;
	float forearmz = bodyz / 2;
	float thighx = bodyx * 0.5;
	float thighy = bodyy * 0.5;
	float thighz = bodyz * 0.75;
	float legx = thighx / 2;
	float legy = thighy;
	float legz = thighz;
	float solex = thighx;
	float soley = legy / 4;
	float solez = thighz;
	float pyramid = thighx;
	// draw the floor
	setAmbientColor(.1f, .1f, .1f);
	setDiffuseColor(COLOR_RED);
	glPushMatrix();

	//// Trying to have texture
	//glEnable(GL_TEXTURE_2D);
	//texture_alloc("Durandal.jpg");

	//	glBegin(GL_QUADS);
	//		glNormal3d(0, 0, -1.0);
	//		glTexCoord2f(0.0, 1.0); glVertex3d(1.0, 0.0, 0.0);
	//		glTexCoord2f(0.0, 0.0); glVertex3d(1.0, 8.0, 0.0);
	//		glTexCoord2f(1.0, 0.0); glVertex3d(9.0, 8.0, 0.0);
	//		glTexCoord2f(1.0, 1.0); glVertex3d(9.0, 0.0, 0.0);
	//	glEnd();
	//glDisable(GL_TEXTURE_2D);
	//// 


	setAmbientColor(.1f, .1f, .1f);
	glTranslated(-5, 0, -5);
	drawBox(10, 0.01f, 10);
	glPopMatrix();

	// draw the sample model
	setAmbientColor(.1f, .1f, .1f);
	setDiffuseColor(COLOR_BLUE);
	glPushMatrix();
	//glTranslated(VAL(XPOS), VAL(YPOS), VAL(ZPOS));

	// rotate the whole body
	glTranslated(0, 1.5 * bodyy, 0);
	glRotated(VAL(WHOLEX), 1.0, 0.0, 0.0);
	glRotated(VAL(WHOLEY), 0.0, 1.0, 0.0);
	glRotated(VAL(WHOLEZ), 0.0, 0.0, 1.0);


	//draw body
	//glPushMatrix();
	//glTranslated(-1.5, 0, -2);
	//glScaled(3, 1, 4);
	drawTexture(bodyx, bodyy, bodyz);
	//glPopMatrix();

	// draw head
	glPushMatrix();

	glTranslated(bodyx / 2, bodyy + headr, bodyz / 2);
	glRotated(VAL(HEADX), 1.0, 0.0, 0.0);
	glRotated(VAL(HEADY), 0.0, 1.0, 0.0);
	glRotated(VAL(HEADZ), 0.0, 0.0, 1.0);
	drawSphere(headr);
	glPopMatrix();

	//draw right arm (Level 2)
	glPushMatrix();
	glTranslated(bodyx, bodyy, bodyz / 2);
	glRotated(VAL(RIGHTARMX), 1.0, 0.0, 0.0);
	glRotated(VAL(RIGHTARMY), 0.0, 1.0, 0.0);
	glRotated(VAL(RIGHTARMZ), 0.0, 0.0, 1.0);
	drawBox(armx, army, armz);
	//draw right forearm (Level 3)
	glPushMatrix();
	glTranslated(0, army, 0);
	glRotated(VAL(RIGHTFOREARMZ), 1.0, 0.0, 0.0);
	glRotated(VAL(RIGHTFOREARMY), 0.0, 1.0, 0.0);
	glRotated(VAL(RIGHTFOREARMX), 0.0, 0.0, 1.0);
	drawBox(armx, army, armz);
	glPopMatrix();
	glPopMatrix();

	//draw left arm (Level 2)
	glPushMatrix();
	glTranslated(-armx, bodyy, bodyz / 2);
	glTranslated(armx, 0, 0);
	glRotated(VAL(LEFTARMX), 1.0, 0.0, 0.0);
	glRotated(VAL(LEFTARMY), 0.0, 1.0, 0.0);
	glRotated(VAL(LEFTARMZ), 0.0, 0.0, 1.0);
	glTranslated(-armx, 0, 0);
	drawBox(armx, army, armz);
	//draw left forearm (Level 3)
	glPushMatrix();
	glTranslated(0, army, 0);
	glRotated(VAL(LEFTFOREARMX), 1.0, 0.0, 0.0);
	glRotated(VAL(LEFTFOREARMY), 0.0, 1.0, 0.0);
	glRotated(VAL(LEFTFOREARMZ), 0.0, 0.0, 1.0);
	drawBox(armx, army, armz);
	glPopMatrix();
	glPopMatrix();

	//draw right thigh (Level 2)
	glPushMatrix();
	glTranslated(bodyx, 0, bodyz / 2);
	glRotated(VAL(RIGHTTHIGHX), 1.0, 0.0, 0.0);
	glRotated(VAL(RIGHTTHIGHY), 0.0, 1.0, 0.0);
	glRotated(VAL(RIGHTTHIGHZ), 0.0, 0.0, 1.0);
	glPushMatrix();
	glTranslated(-thighx / 2, -thighy, -thighz / 2);
	drawBox(thighx, thighy, thighz);
	glPopMatrix();
	//draw right leg (Level 3)
	glPushMatrix();
	glTranslated(0, -thighy, 0);
	glRotated(VAL(RIGHTLEGX), 1.0, 0.0, 0.0);
	glRotated(VAL(RIGHTLEGY), 0.0, 1.0, 0.0);
	glRotated(VAL(RIGHTLEGZ), 0.0, 0.0, 1.0);
	glPushMatrix();
	glTranslated(-legx / 2, -legy, -legz / 2);
	drawBox(legx, legy, legz);
	glPopMatrix();
	//draw right sole (Level 4)
	glPushMatrix();
	glTranslated(0, -legy, 0);
	/*glRotated(VAL(RIGHTSOLEX), 1.0, 0.0, 0.0);
	glRotated(VAL(RIGHTSOLEY), 0.0, 1.0, 0.0);*/
	glRotated(VAL(RIGHTSOLEX), 1.0, 0.0, 0.0);
	drawPyramid(0.87 * pyramid, 0, -pyramid / 2,
		-0.87 * pyramid, 0, -pyramid / 2,
		0, 0, pyramid,
		0, -pyramid, 0);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	//draw left thigh (Level 2)
	glPushMatrix();
	glTranslated(0, 0, bodyz / 2);
	glRotated(VAL(LEFTTHIGHX), 1.0, 0.0, 0.0);
	glRotated(VAL(LEFTTHIGHY), 0.0, 1.0, 0.0);
	glRotated(VAL(LEFTTHIGHZ), 0.0, 0.0, 1.0);
	glPushMatrix();
	glTranslated(-thighx / 2, -thighy, -thighz / 2);
	drawBox(thighx, thighy, thighz);
	glPopMatrix();
	//draw left leg (Level 3)
	glPushMatrix();
	glTranslated(0, -thighy, 0);
	glRotated(VAL(LEFTLEGX), 1.0, 0.0, 0.0);
	glRotated(VAL(LEFTLEGY), 0.0, 1.0, 0.0);
	glRotated(VAL(LEFTLEGZ), 0.0, 0.0, 1.0);
	glPushMatrix();
	glTranslated(-legx / 2, -legy, -legz / 2);
	drawBox(legx, legy, legz);
	glPopMatrix();
	//draw left sole (Level 4)
	glPushMatrix();
	glTranslated(0, -legy, 0);
	/*glRotated(VAL(RIGHTSOLEX), 1.0, 0.0, 0.0);
	glRotated(VAL(RIGHTSOLEY), 0.0, 1.0, 0.0);*/
	glRotated(VAL(LEFTSOLEX), 1.0, 0.0, 0.0);
	drawPyramid(0.87 * pyramid, 0, -pyramid / 2,
		-0.87 * pyramid, 0, -pyramid / 2,
		0, 0, pyramid,
		0, -pyramid, 0);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
}
//WHOLEX, WHOLEY, WHOLEZ,
//HEADX, HEADY, HEADZ,
//LEFTARMX, LEFTARMY, LEFTARMZ,
//RIGHTARMX, RIGHTARMY, RIGHTARMZ,
//LEFTFOREARMX, LEFTFOREARMY, LEFTFOREARMZ,
//RIGHTFOREARMX, RIGHTFOREARMY, RIGHTFOREARMZ,
//LEFTPALMX, LEFTPALMY, LEFTPALMZ,
//RIGHTPALMX, RIGHTPALMY, RIGHTPALMZ,
//LEFTTHIGHX, LEFTTHIGHY, LEFTTHIGHZ,
//RIGHTTHIGHX, RIGHTTHIGHY, RIGHTTHIGHZ,
//LEFTLEGX, LEFTLEGY, LEFTLEGZ,
//RIGHTLEGX, RIGHTLEGY, RIGHTLEGZ,
int main()
{
	// Initialize the controls
	// Constructor is ModelerControl(name, minimumvalue, maximumvalue, 
	// stepsize, defaultvalue)
	ModelerControl controls[NUMCONTROLS];
	/*controls[WHOLEX] = ModelerControl("WHOLEX", -180, 180, 1, 0);
	controls[WHOLEY] = ModelerControl("WHOLEY", -180, 180, 1, 0);
	controls[WHOLEZ] = ModelerControl("WHOLEZ", -180, 180, 1, 0);
	controls[HEIGHT] = ModelerControl("Height", 1, 2.5, 0.1f, 1);
	controls[ROTATE] = ModelerControl("Rotate", -135, 135, 1, 0);*/
	/*WHOLEX, WHOLEY, WHOLEZ,
		HEADX, HEADY, HEADZ,
		LEFTARMX, LEFTARMY, LEFTARMZ,
		RIGHTARMX, RIGHTARMY, RIGHTARMZ,
		LEFTFOREARMX, LEFTFOREARMY, LEFTFOREARMZ,
		RIGHTFOREARMX, RIGHTFOREARMY, RIGHTFOREARMZ,
		LEFTTHIGHX, LEFTTHIGHY, LEFTTHIGHZ,
		RIGHTTHIGHX, RIGHTTHIGHY, RIGHTTHIGHZ,
		LEFTLEGX, LEFTLEGY, LEFTLEGZ,
		RIGHTLEGX, RIGHTLEGY, RIGHTLEGZ,
		LEFTSOLEX,
		RIGHTSOLEX,*/
	controls[WHOLEX] = ModelerControl("whole rotate x", -180, 180, 1, 0);
	controls[WHOLEY] = ModelerControl("whole rotate y", -180, 180, 1, 0);
	controls[WHOLEZ] = ModelerControl("whole rotate z", -180, 180, 1, 0);
	controls[HEADX] = ModelerControl("head rotate x", -180, 180, 1, 0);
	controls[HEADY] = ModelerControl("head rotate y", -180, 180, 1, 0);
	controls[HEADZ] = ModelerControl("head rotate z", -180, 180, 1, 0);
	controls[LEFTARMX] = ModelerControl("leftarm rotate x", -180, 180, 1, 0);
	controls[LEFTARMY] = ModelerControl("leftarm rotate y", -180, 180, 1, 0);
	controls[LEFTARMZ] = ModelerControl("leftarm rotate z", -180, 180, 1, 0);
	controls[RIGHTARMX] = ModelerControl("rightarm rotate x", -180, 180, 1, 0);
	controls[RIGHTARMY] = ModelerControl("rightarm rotate y", -180, 180, 1, 0);
	controls[RIGHTARMZ] = ModelerControl("rightarm rotate z", -180, 180, 1, 0);
	controls[LEFTFOREARMX] = ModelerControl("leftforearm rotate x", -180, 180, 1, 0);
	controls[LEFTFOREARMY] = ModelerControl("leftforearm rotate y", -180, 180, 1, 0);
	controls[LEFTFOREARMZ] = ModelerControl("leftforearm rotate z", -180, 180, 1, 0);
	controls[RIGHTFOREARMX] = ModelerControl("rightforearm rotate x", -180, 180, 1, 0);
	controls[RIGHTFOREARMY] = ModelerControl("rightforearm rotate x", -180, 180, 1, 0);
	controls[RIGHTFOREARMZ] = ModelerControl("rightforearm rotate x", -180, 180, 1, 0);
	controls[LEFTTHIGHX] = ModelerControl("left thigh rotate x", -180, 180, 1, 0);
	controls[LEFTTHIGHY] = ModelerControl("left thigh rotate y", -180, 180, 1, 0);
	controls[LEFTTHIGHZ] = ModelerControl("left thigh rotate z", -180, 180, 1, 0);
	controls[RIGHTTHIGHX] = ModelerControl("right thigh rotate x", -180, 180, 1, 0);
	controls[RIGHTTHIGHY] = ModelerControl("right thigh rotate y", -180, 180, 1, 0);
	controls[RIGHTTHIGHZ] = ModelerControl("right thigh rotate z", -180, 180, 1, 0);
	controls[LEFTLEGX] = ModelerControl("left leg rotate x", -180, 180, 1, 0);
	controls[LEFTLEGY] = ModelerControl("left leg rotate y", -180, 180, 1, 0);
	controls[LEFTLEGZ] = ModelerControl("left leg rotate z", -180, 180, 1, 0);
	controls[RIGHTLEGX] = ModelerControl("right leg rotate x", -180, 180, 1, 0);
	controls[RIGHTLEGY] = ModelerControl("right leg rotate y", -180, 180, 1, 0);
	controls[RIGHTLEGZ] = ModelerControl("right leg rotate z", -180, 180, 1, 0);
	controls[LEFTSOLEX] = ModelerControl("left sole rotate x", -180, 180, 1, 0);
	controls[RIGHTSOLEX] = ModelerControl("right sole rotate x", -180, 180, 1, 0);
	/*for (int i = 0; i < NUMCONTROLS; i++) {
	controls[i]= ModelerControl("test", -180, 180, 1, 0);
	}*/
	ModelerApplication::Instance()->Init(&createSampleModel, controls, NUMCONTROLS);
	return ModelerApplication::Instance()->Run();
}
