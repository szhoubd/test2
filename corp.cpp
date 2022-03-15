// The sample model.  You should build a file
// very similar to this for when you make your model.
#include "modelerview.h"
#include "modelerapp.h"
#include "modelerdraw.h"
#include <FL/gl.h>

#include "modelerglobals.h"

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
	float headr = bodyx*3/8;
	float armx = bodyx / 4;
	float army = bodyy / 3;
	float armz = bodyz / 2;
	float forearmx = bodyx / 4;
	float forearmy = bodyy / 3;
	float forearmz = bodyz / 2;
	float thighx = bodyx * 0.5;
	float thighy = bodyy*0.5;
	float thighz = bodyz * 0.75;
	float legx = thighx / 2;
	float legy = thighy ;
	float legz = thighz;
	float solex = thighx;
	float soley = legy/4;
	float solez = thighz;
	// draw the floor
	setAmbientColor(.1f, .1f, .1f);
	setDiffuseColor(COLOR_RED);
	glPushMatrix();
	glTranslated(-5, 0, -5);
	drawBox(10, 0.01f, 10);
	glPopMatrix();

	// draw the sample model
	setAmbientColor(.1f, .1f, .1f);
	setDiffuseColor(COLOR_BLUE);
	glPushMatrix();
	//glTranslated(VAL(XPOS), VAL(YPOS), VAL(ZPOS));

	// rotate the whole body
	glTranslated(0, 1.5*bodyy,0);
	glRotated(VAL(WHOLEX), 1.0, 0.0, 0.0);
	glRotated(VAL(WHOLEY), 0.0, 1.0, 0.0);
	glRotated(VAL(WHOLEZ), 0.0, 0.0, 1.0);


	//draw body
	//glPushMatrix();
	//glTranslated(-1.5, 0, -2);
	//glScaled(3, 1, 4);
	drawBox(bodyx, bodyy, bodyz);
	//glPopMatrix();

	// draw head
	glPushMatrix();
	
	glTranslated(bodyx/2, bodyy +headr, bodyz / 2);
	glRotated(VAL(HEADX), 1.0, 0.0, 0.0);
	glRotated(VAL(HEADY), 0.0, 1.0, 0.0);
	glRotated(VAL(HEADZ), 0.0, 0.0, 1.0);
	drawSphere(headr);
	glPopMatrix();

	//draw right arm
	glPushMatrix();
	glTranslated(bodyx , bodyy , bodyz / 2);
	glRotated(VAL(RIGHTARMX), 1.0, 0.0, 0.0);
	glRotated(VAL(RIGHTARMY), 0.0, 1.0, 0.0);
	glRotated(VAL(RIGHTARMZ), 0.0, 0.0, 1.0);
	drawBox(armx, army, armz);
	glPopMatrix();

	//draw left arm
	glPushMatrix();
	glTranslated(-armx, bodyy, bodyz / 2);
	glTranslated(armx, 0, 0);
	glRotated(VAL(LEFTARMX), 1.0, 0.0, 0.0);
	glRotated(VAL(LEFTARMY), 0.0, 1.0, 0.0);
	glRotated(VAL(LEFTARMZ), 0.0, 0.0, 1.0);
	glTranslated(-armx, 0,0);
	drawBox(armx, army, armz);
	glPopMatrix();

	//draw right forearm
	glPushMatrix();
	glTranslated(bodyx, bodyy, bodyz / 2);
	glRotated(VAL(RIGHTARMX), 1.0, 0.0, 0.0);
	glRotated(VAL(RIGHTARMY), 0.0, 1.0, 0.0);
	glRotated(VAL(RIGHTARMZ), 0.0, 0.0, 1.0);
	glTranslated(0, army, 0);
	glRotated(VAL(RIGHTFOREARMZ), 1.0, 0.0, 0.0);
	glRotated(VAL(RIGHTFOREARMY), 0.0, 1.0, 0.0);
	glRotated(VAL(RIGHTFOREARMX), 0.0, 0.0, 1.0);
	drawBox(armx, army, armz);
	glPopMatrix();

	//draw left forearm
	glPushMatrix();
	glTranslated(0, bodyy, bodyz / 2);
	glRotated(VAL(LEFTARMX), 1.0, 0.0, 0.0);
	glRotated(VAL(LEFTARMY), 0.0, 1.0, 0.0);
	glRotated(VAL(LEFTARMZ), 0.0, 0.0, 1.0);
	glTranslated(0, army, 0);
	glRotated(VAL(LEFTFOREARMX), 1.0, 0.0, 0.0);
	glRotated(VAL(LEFTFOREARMY), 0.0, 1.0, 0.0);
	glRotated(VAL(LEFTFOREARMZ), 0.0, 0.0, 1.0);
	glTranslated(-armx, 0, 0);
	drawBox(armx, army, armz);
	glPopMatrix();


	//draw right thigh
	glPushMatrix();
	glTranslated(bodyx, 0, bodyz / 2);
	glRotated(VAL(RIGHTTHIGHX), 1.0, 0.0, 0.0);
	glRotated(VAL(RIGHTTHIGHY), 0.0, 1.0, 0.0);
	glRotated(VAL(RIGHTTHIGHZ), 0.0, 0.0, 1.0);
	glTranslated(-thighx/2, -thighy, -thighz/2);
	drawBox(thighx, thighy, thighz);
	glPopMatrix();

	//draw left thigh
	glPushMatrix();
	glTranslated(0, 0, bodyz / 2);
	glRotated(VAL(LEFTTHIGHX), 1.0, 0.0, 0.0);
	glRotated(VAL(LEFTTHIGHY), 0.0, 1.0, 0.0);
	glRotated(VAL(LEFTTHIGHZ), 0.0, 0.0, 1.0);
	glTranslated(-thighx / 2, -thighy, -thighz / 2);
	drawBox(thighx, thighy, thighz);
	glPopMatrix();

	//draw right leg
	glPushMatrix();
	glTranslated(bodyx, 0, bodyz / 2);
	glRotated(VAL(RIGHTTHIGHX), 1.0, 0.0, 0.0);
	glRotated(VAL(RIGHTTHIGHY), 0.0, 1.0, 0.0);
	glRotated(VAL(RIGHTTHIGHZ), 0.0, 0.0, 1.0);
	glTranslated(0, -thighy, 0);
	glRotated(VAL(RIGHTLEGX), 1.0, 0.0, 0.0);
	glRotated(VAL(RIGHTLEGY), 0.0, 1.0, 0.0);
	glRotated(VAL(RIGHTLEGZ), 0.0, 0.0, 1.0);
	glTranslated(-legx / 2, -legy, -legz / 2);
	drawBox(legx, legy, legz);
	glPopMatrix();

	//draw left leg
	glPushMatrix();
	glTranslated(0, 0, bodyz / 2);
	glRotated(VAL(LEFTTHIGHX), 1.0, 0.0, 0.0);
	glRotated(VAL(LEFTTHIGHY), 0.0, 1.0, 0.0);
	glRotated(VAL(LEFTTHIGHZ), 0.0, 0.0, 1.0);
	glTranslated(0, -thighy, 0);
	glRotated(VAL(LEFTTHIGHX), 1.0, 0.0, 0.0);
	glRotated(VAL(LEFTTHIGHY), 0.0, 1.0, 0.0);
	glRotated(VAL(LEFTTHIGHZ), 0.0, 0.0, 1.0);
	glTranslated(-legx / 2, -legy, -legz / 2);
	drawBox(legx, legy, legz);
	glPopMatrix();

	//draw right sole
	glPushMatrix();
	glTranslated(bodyx, 0, bodyz / 2);
	glRotated(VAL(RIGHTTHIGHX), 1.0, 0.0, 0.0);
	glRotated(VAL(RIGHTTHIGHY), 0.0, 1.0, 0.0);
	glRotated(VAL(RIGHTTHIGHZ), 0.0, 0.0, 1.0);
	glTranslated(0, -thighy, 0);
	glRotated(VAL(RIGHTLEGX), 1.0, 0.0, 0.0);
	glRotated(VAL(RIGHTLEGY), 0.0, 1.0, 0.0);
	glRotated(VAL(RIGHTLEGZ), 0.0, 0.0, 1.0);
	glTranslated(0, -legy, 0);
	/*glRotated(VAL(RIGHTSOLEX), 1.0, 0.0, 0.0);
	glRotated(VAL(RIGHTSOLEY), 0.0, 1.0, 0.0);*/
	glRotated(VAL(RIGHTSOLEX), 1.0, 0.0, 0.0);
	glTranslated(-solex / 2, -soley, -solez / 2);
	drawBox(solex, soley, solez);
	glPopMatrix();

	//draw left sole
	glPushMatrix();
	glTranslated(0, 0, bodyz / 2);
	glRotated(VAL(LEFTTHIGHX), 1.0, 0.0, 0.0);
	glRotated(VAL(LEFTTHIGHY), 0.0, 1.0, 0.0);
	glRotated(VAL(LEFTTHIGHZ), 0.0, 0.0, 1.0);
	glTranslated(0, -thighy, 0);
	glRotated(VAL(LEFTLEGX), 1.0, 0.0, 0.0);
	glRotated(VAL(LEFTLEGY), 0.0, 1.0, 0.0);
	glRotated(VAL(LEFTLEGZ), 0.0, 0.0, 1.0);
	glTranslated(0, -legy, 0);
	/*glRotated(VAL(RIGHTSOLEX), 1.0, 0.0, 0.0);
	glRotated(VAL(RIGHTSOLEY), 0.0, 1.0, 0.0);*/
	glRotated(VAL(LEFTSOLEX), 1.0, 0.0, 0.0);
	glTranslated(-solex / 2, -soley, -solez / 2);
	drawBox(solex, soley, solez);
	glPopMatrix();
	/*glTranslated(0.0, 0.0, VAL(HEIGHT));
	drawCylinder(1, 1.0, 0.9);

	glTranslated(0.0, 0.0, 0.5);
	glRotated(90, 1.0, 0.0, 0.0);
	drawCylinder(4, 0.1, 0.2);*/
	

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
	for (int i = 0; i < NUMCONTROLS; i++) {
	controls[i]= ModelerControl("test", -180, 180, 1, 0);
	}
	ModelerApplication::Instance()->Init(&createSampleModel, controls, NUMCONTROLS);
	return ModelerApplication::Instance()->Run();
}
