#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
//#include <gl/GLU.h>
#include <ctime>
#include <cmath>
#include "imageloader.h"
#include "md2Model.h"
#include <string>



using namespace std;





int playerLife = 10;


int pause = 0;
float Pi = 3.14159265f;
int  isSky = 0;
GLfloat mat_ambient[] = { 1, 1, 1, 1.0 };
GLfloat mat_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat mat_shininess[] = { 50.0 };

GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat light_diffuse[] = { 1, 1, 1, 1.0 };
GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light_position[] = { 0, 1, 0, 0.1 };

GLfloat light_position2[] = { 0, 0, -0.1, 0.1 };

MD2Model* _model;
int _textureId;


int fps = 20;
int width = 800, height = 600;


int num_of_enemies = 100;
int enemy_is_dead[100] = { 0 }; // equal to number of enemies
int enemy_collide[100] = { 0 };
float lastCoeff[100] = { 0 };





float player_diameter = 1, player_maxz = 0.2, player_minz = 0.2;

float player_timer = 100;
float bonusBasePose = 0;
bool end_game = false;
float x_prev = 0, y_prev = 0;


float bullet_size = 0.05;
int bullet_max = 99;
int bullet_idx = 0;
int bullet_num = 0;
float bullet_init_x[100] = { 0 }, bullet_init_y[100] = { 0 }, bullet_init_z[100] = { 0 };
float bullet_added_z[100] = { 0 }, bullet_set_flag[100] = { 0 };
float bullet_x[100] = { 0 }, bullet_y[100] = { 0 }, bullet_z[100] = { 0 };


int bonus_timer[100] = { 0 };


int isBullet = 0, isPlayer = 0;



float shield_color[4] = { 0, 1, 1 ,0.2};
int shield_timer = 0;

float player_speed = -0.01, enemies_base_speed = 0.1, enemiesBasePose = 0;



float cameraPose[3] = { 0, 0, 0 };
float playerPose[3] = { 0, -1, -3 };
float playerPoseFlag[3] = { 0, 0, 0 };
float cameraDirection[3] = { 0, 0, -1 };

float bullet_pose = 0;

float baseRadious = 0.1;




GLUquadric *quad_for_sphere;
GLuint FireId,ShieldId,Ab1Id,Ab2Id, RockId,BonusId, SkyId, BulletId;
float baseRotateAngle;

float sndFlag = 0;




GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId); 
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->width, image->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);              
	return textureId; 
}
void cleanup() {
	delete _model;
}
void reset(){
	
	
	

	cameraPose[0] = 0.5;
	cameraPose[1] = 0.2;
	cameraPose[2] = 0;

	playerPose[0] = 0;
	playerPose[1] = 0;
	playerPose[2] = -1;

	playerPoseFlag[0] = 0;
	playerPoseFlag[1] = 0;
	playerPoseFlag[2] = -1;

	cameraDirection[0] = 0;
	cameraDirection[1] = 0;
	cameraDirection[2] = 0;



	enemiesBasePose = 0;
	baseRotateAngle = 0;


	fps = 20;
	playerLife = 10;



	pause = 0;
	
	isSky = 0;

	mat_ambient[0] = 1,mat_ambient[1] = 1,mat_ambient[2] = 1,mat_ambient[3] = 1;
	mat_diffuse[0] = 0.8, mat_diffuse[1] = 0.8, mat_diffuse[2] = 0.8, mat_diffuse[3] = 1;
	mat_specular[0] = 1, mat_specular[1] = 1, mat_specular[2] = 1, mat_specular[3] = 1;
	mat_shininess[0] = 50;

	light_ambient[0] = 0, light_ambient[1] = 0, light_ambient[2] = 0, light_ambient[3] = 1;
	light_diffuse[0] = 1, light_diffuse[1] = 1, light_diffuse[2] = 1, light_diffuse[3] = 1;
	light_specular[0] = 1, light_specular[1] = 1, light_specular[2] = 1, light_specular[3] = 1;
	light_position[0] = 0, light_position[1] = 1, light_position[2] = 0, light_position[3] = 0.1f;

	light_position2[0] = 0, light_position2[1] = 0, light_position2[2] = -0.1, light_position2[3] = 0.1f;
	


	


	num_of_enemies = 100;

	for (int i = 0; i < 100; i++)
	{
		enemy_is_dead[i] = 0; 
		enemy_collide[i] =  0 ;
		lastCoeff[i] =  0 ;
		bullet_init_x[i] =  0 , bullet_init_y[i] =  0 , bullet_init_z[i] =  0 ;
		bullet_added_z[i] =  0 , bullet_set_flag[i] =  0 ;
		bullet_x[i] = 0 , bullet_y[i] = 0 , bullet_z[i] =  0 ;
		bonus_timer[i] =  0 ;
	}


	player_diameter = 1, player_maxz = 0.2, player_minz = 0.2;

	player_timer = 100;
	bonusBasePose = 0;
	end_game = false;
	x_prev = 0, y_prev = 0;


	bullet_size = 0.05;
	bullet_max = 99;
	bullet_idx = 0;
	bullet_num = 0;
	isBullet = 0, isPlayer = 0;


	shield_color[0] = 0, shield_color[0] = 1, shield_color[0] = 1, shield_color[0] = 0.2;
	
	shield_timer = 0;

	player_speed = -0.01, enemies_base_speed = 0.1, enemiesBasePose = 0;




	bullet_pose = 0;
	baseRadious = 0.1;
	sndFlag = 0;

}
void init(void)
{
	
	glClearColor(0, 0, 0, 1.0); 
	glPointSize(4.0);
	glShadeModel(GL_SMOOTH);
	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);


	
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	


	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT1, GL_POSITION, light_position2);
	glEnable(GL_LIGHT1);


	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	quad_for_sphere = gluNewQuadric();

	Image *img1,*img2, *img3, *img4, *img5, *img6;
	img1 = loadBMP("fire.bmp");
	img2 = loadBMP("rock.bmp");
	img3 = loadBMP("lightning1.bmp"); 
	img4 = loadBMP("lightning2.bmp");
	img5 = loadBMP("shield.bmp");
	img6 = loadBMP("sky_panaroma.bmp");
	

	FireId = loadTexture(img1); // fire for explosion
	RockId = loadTexture(img2); // rock enemy
	BonusId = loadTexture(img3); // blue lightning for bonus
	BulletId = loadTexture(img4); // lightning for bullets
	ShieldId = loadTexture(img5); // shield
	SkyId = loadTexture(img6); // sky texture

	_model = MD2Model::load("fighter/fighter.md2");
	if (_model != NULL) {
		_model->setAnimation("fighter");
	}

	

	reset();
	PlaySound(L"transformers.wav", NULL, SND_ASYNC | SND_FILENAME | SND_LOOP );



	delete img1, img2, img3, img4, img5, img6;
}





void glPrint(string message, float x, float y, float z)
{
	
	glRasterPos3f(x, y,z);

	for (int c = 0; c < message.length(); c++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, message[c]);
	}
}


void Sphere(float pose_x, float pose_y, float pose_z, float rotate_angle, float tilt_angle, float eskew_angle, GLuint textureId, float diameter, int slices, float r, float g, float b, float a)
{
	glPushMatrix();
	glColor4f(r, g, b, a);
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, textureId);



	glTranslatef(pose_x, pose_y, pose_z);
	glRotatef(tilt_angle, 1, 0, 0);
	glRotatef(rotate_angle, 0.0f, 0.0f, 1.0f);
	glRotatef(tilt_angle, 1, 0, 0);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	gluQuadricTexture(quad_for_sphere, 1);
	if (isBullet)
	{
		GLfloat mat_em[] = { r,g, b, a };
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mat_em);
	}
	else
	{
		GLfloat mat_em[] = { 0.0, 0.0, 0.0, 0.0 };
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mat_em);
	}
	if (isSky)
		glRotatef(90, 1, 0, 0);

	gluSphere(quad_for_sphere, diameter, slices, slices);


	glPopMatrix();

}

void draw_shield(float x,float y,float z,float color[],float radius,GLuint tex_Id)
{
	// draw the shield
	light_ambient[0] = light_ambient[1] = light_ambient[2] = 0.5;
	light_ambient[3] = 1.f;

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_ambient);


	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// apply transparent mat
	mat_ambient[0] = mat_ambient[1] = mat_ambient[2] = mat_ambient[3] = 0;
	mat_diffuse[0] = mat_diffuse[1] = mat_diffuse[2] = 0;
	mat_diffuse[3] = 0;
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);

	Sphere(x, y, z, 0, 0, 0, tex_Id, radius, 50,
		color[0], color[1], color[2], color[3]);
	light_ambient[0] = light_ambient[1] = light_ambient[2] = 0.1f;
	light_ambient[3] = 1.f;
	glColor4f(1, 1, 1, 1);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_ambient);
	glDisable(GL_BLEND);

	// apply opaque mat
	mat_ambient[0] = mat_ambient[1] = mat_ambient[2] = mat_ambient[3] = 1;
	mat_diffuse[0] = mat_diffuse[1] = mat_diffuse[2] = mat_diffuse[3] = 1;

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
	// end of shield draw
}

bool isCollided(float enemy_pose[],float enemy_diameter,float playerPose[],float player_diameter,float player_maxz,float player_minz,float z_offset)
{
	float distance;
	distance = sqrt(pow((enemy_pose[0] - playerPose[0]), 2) + pow((enemy_pose[1] - playerPose[1]), 2)
		+ pow(max((abs(-enemy_pose[2] + playerPose[2])-z_offset),0), 2));
	if (distance < (enemy_diameter + player_diameter))
	{
		if ((playerPose[1] - enemy_pose[1]) < player_minz && (playerPose[1] - enemy_pose[1]) > 0)
		{
			return true;
		}
		else if ((enemy_pose[1] - playerPose[1]) < player_maxz && (enemy_pose[1] - playerPose[1]) > 0)
		{
			return true;
		}
	}
	return false;
}

void handleCollideOfPlayer(int enemy_number)
{
	shield_color[0] = 1;
	shield_color[1] = 0;
	shield_color[2] = 0;
	shield_color[3] = 0.5;
	shield_timer = 20;
	if (enemy_collide[enemy_number] == 0 && playerLife)
		playerLife -= 1;

}

void handleCollideOfEnemy(int i)
{
	enemy_is_dead[i] = 20; // count down timer for explosion of enemy


}


void render(void)


{
	
	

	for (int i = 0; i < 3; i++)
		playerPose[i] += playerPoseFlag[i] * 0.1;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	float AR = ((float)width) / height;
	glDisable(GL_BLEND);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1.0*AR, 1.0*AR, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHT1);
	glDisable(GL_LIGHTING);
	glColor4f(1, 1, 1, 1);
	string life_msg = "Life : " ;
	life_msg.append(to_string(playerLife));
	glPrint(life_msg, -0.92*AR, 0.82, 0);
	glColor4f(0, 0.8, 0.2, 1);
	glBegin(GL_QUADS);


	glColor4f(0, 0.5, 0.2, 0.1);

	glVertex2f(-0.95*AR, 0.8);

	glVertex2f(-0.15*AR, 0.8);

	glVertex2f(-0.15*AR, 0.9);

	glVertex2f(-0.95*AR, 0.9);

	glEnd();
	

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_TEXTURE_2D);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	gluPerspective(45.f, AR, 0.001f, 51000.f);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);

	GLfloat ambientLight[] = { 0.3f, 0.3f, 0.3f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

	GLfloat lightColor[] = { 0.7f, 0.7f, 0.7f, 1.0f };

	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	


	mat_ambient[0] = mat_ambient[1] = mat_ambient[2] = mat_ambient[3] = 0;
	mat_diffuse[0] = mat_diffuse[1] = mat_diffuse[2] = mat_diffuse[3] = 1;

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);

	glLoadIdentity();

	
	
	GLfloat fogColor[] = { 0.2f, 0.2f, 0.2f, 1.0 };
	glFogfv(GL_FOG_COLOR, fogColor);
	glFogi(GL_FOG_MODE, GL_LINEAR);
	glFogf(GL_FOG_DENSITY, 0.007f);
	glHint(GL_FOG_HINT, GL_NICEST);
	glFogf(GL_FOG_START, 0.1);
	glFogf(GL_FOG_END, 60);
	

	

	gluLookAt(cameraPose[0] + playerPose[0] * 1.1,
		cameraPose[1] + playerPose[1] * 1.1,
		cameraPose[2] + playerPose[2] + 3,
		playerPose[0],
		playerPose[1],
		playerPose[2],
		0, 1, 0);

	//sky
	glDisable(GL_FOG);
	isSky = 1;
	isBullet = 1;

	Sphere(playerPose[0], playerPose[1], playerPose[2], 0, 0, 0, SkyId, 100, 200, 1, 1, 1, 1);
	isSky = 0;
	isBullet = 0;
	glEnable(GL_FOG);
	

	glLightfv(GL_LIGHT1, GL_POSITION, light_position2);

	
	light_position2[0] = 0;
	light_position2[1] = 1;
	light_position2[2] = -1;
	//Draw Player Plane
	if (_model != NULL) {
		
		if (playerLife <= 0 && player_timer <= 0)
		{
			glColor4f(0.5, 0.5, 0.5, 1);
			GLfloat mat_em[] = { 0.2 + player_timer / 20.0, -1, -1, 1.0 };
			glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mat_em);
			if (sndFlag == 0)
			{
				PlaySound(L"transformers.wav", NULL, SND_ASYNC | SND_FILENAME);
				sndFlag = 1;
			}
		}
		else if (playerLife <= 0 && player_timer > 0)
		{
			glColor4f(0.5, 0.5, 0.5, 1);
			GLfloat mat_em[] = { 0.2+player_timer/20.0, -1, -1, 1.0 };
			glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mat_em);
			if (player_timer == 99)
				PlaySound(L"explosion.wav", NULL, SND_ASYNC | SND_FILENAME );
		}
		else
		{
			glColor4f(1, 1, 1, 1);
			GLfloat mat_em[] = { 1.0, (playerLife - 4) / 8.0, (playerLife - 4) / 8.0, 1.0 };
			glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mat_em);
		}
		
		mat_specular[0] = 1, mat_specular[1] = 1, mat_specular[2] = 1, mat_specular[3] = 1.0;
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);

		glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
		glEnable(GL_COLOR_MATERIAL);

		
		glPushMatrix();
		glTranslatef(playerPose[0],
			playerPose[1],
			playerPose[2]);
		glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
		glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);


		glScalef(0.01f, 0.01f, 0.01f);
		_model->draw();
		glScalef(100.0f, 100.0f, 100.0f);
		glPopMatrix();
		GLfloat mat_em2[] = { 0.0, 0.0, 0.0, 0.0 };
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mat_em2);
		mat_ambient[0] = 1, mat_ambient[1] = 1, mat_ambient[2] = 1, mat_ambient[3] = 1.0;
		mat_diffuse[0] = 0.8, mat_diffuse[1] = 0.8, mat_diffuse[2] = 0.8, mat_diffuse[3] = 1.0;
		mat_specular[0] = 1, mat_specular[1] = 1, mat_specular[2] = 1, mat_specular[3] = 1.0;
		mat_shininess[0] = 50.0;
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
		glColor4f(1, 1, 1, 1);
	}
	// end of the player draw
	
	


	// draw bullets
	GLfloat mat_em[] = { 1.0, 1.0, 1.0, 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mat_em);

	for (int i = 0; i < bullet_num; i++){

		if (!pause && (bullet_set_flag[i] == 0))
		{
			bullet_init_x[i] = playerPose[0];
			bullet_init_y[i] = playerPose[1];
			bullet_init_z[i] = playerPose[2];

			bullet_added_z[i] = 0.5;
			bullet_set_flag[i] = 1;
		}
		glColor4f(1, 1, 1, 1);

		isSky = 1;
		isBullet = 1;
		Sphere(bullet_init_x[i], bullet_init_y[i], playerPose[2] - bullet_added_z[i], 0, 0, 0, FireId, bullet_size, 50, 1, 0.5, 0, 1);
		
		Sphere(bullet_init_x[i], bullet_init_y[i], playerPose[2] - bullet_added_z[i], baseRotateAngle*3, 0, 0, BulletId, bullet_size*1.5, 50, 0.5, 0, 0, 0.3);

		if (!pause)
			bullet_added_z[i] += 1;
		if ((bullet_init_z[i] - bullet_added_z[i]) < -1)
		{
			//
		}
	}

	GLfloat mat_em2[] = { 0.0, 0.0, 0.0, 0.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mat_em2);
	glEnable(GL_FOG);
	isSky = 0;
	isBullet = 0;

	

	// draw enemies

	int coeff = 1;
	float enemy_pose[3] = { 0 };
	float enemy_diameter;
	for (int i = 0; i < num_of_enemies; i++)
	{
		if (enemy_is_dead[i])
		{
			if (enemy_is_dead[i] == 1)
			{
				continue;
			}
			else
			{
				if (!pause)
					enemy_is_dead[i] -= 1;
				continue;
			}
		}
		float dist = enemiesBasePose*(2 + 1.5*cos(i));
		if ((dist - 3 - 2 * i + playerPose[2]) >(playerPose[2] + 15))
		{
			coeff = (dist - 3 - 2 * i + playerPose[2] - playerPose[2] - 15) / (num_of_enemies + 15 + 3);
			dist -= (coeff + 1)*(num_of_enemies + 15 + 3);
			
			if (shield_timer < 1)
				enemy_collide[i] = 0;
			lastCoeff[i] = coeff;
		}

		enemy_pose[0] = playerPose[0] * 0.8 + 2 * tan(i)*sin(i);
		enemy_pose[1] = playerPose[1] * 0.8 + 2 * tan(6 * i)*cos(50 * i);
		enemy_pose[2] = dist - 3 - i + playerPose[2];
		enemy_diameter = baseRadious *0.5*(4 + 3 * sin(3 * i));
		Sphere(enemy_pose[0], enemy_pose[1], enemy_pose[2], baseRotateAngle * 6 * 1000 * i, 90, sin(i) * 90, RockId,
			enemy_diameter, 30-abs(enemy_pose[2]-playerPose[2])/6, (1 + sin(i)) / 2, (1 + cos(i)) / 2, (1 + tan(i)) / 2, 1);

		// Check for Collisions of Enemy/Player
		if (isCollided(enemy_pose, enemy_diameter, playerPose, player_diameter, 
			player_maxz* player_diameter + enemy_diameter, player_minz*player_diameter + enemy_diameter,
			0.5*(enemies_base_speed*(2 + 1.5*cos(i))+player_speed)
			))
		{
			handleCollideOfPlayer(i);
			enemy_collide[i] = 1;
		}

		// Check for Collisions of Bullet/Enemy
		for (int j = 0; j < bullet_num; j++)
		{
			float bulletPose[3] = { bullet_init_x[j], bullet_init_y[j], playerPose[2] - bullet_added_z[j] + 1 };
			if (isCollided(enemy_pose, enemy_diameter, bulletPose, bullet_size, bullet_size + enemy_diameter, bullet_size + enemy_diameter,
				0.5*(1 + enemies_base_speed*(2 + 1.5*cos(i)))
				
				))
			{
				handleCollideOfEnemy(i);
				
				
			}
		}
		
	}

	// end of draw enemies
	

	
	// draw bonus spheres
	glPushMatrix();
	if (!pause)
	{
		if (bonusBasePose <= 4.1 && bonusBasePose >= 3.9)
			bonusBasePose = 0;
		bonusBasePose += 0.2;

	}
	for (int i = 0; i < 100; i++)
	{
		float bonus_pose[3] = { 0, 0, 10 - 4 * i + playerPose[2] + bonusBasePose };
		if (bonus_timer[i])
			bonus_timer[i]--;
		else
		{
			glDisable(GL_FOG);
			isSky = 1;
			isBullet = 1;
			Sphere(bonus_pose[0], bonus_pose[1], bonus_pose[2], 0, 0, 0, BonusId, baseRadious * 0.8, 50, 1, 1, 0, 1);
			
			// check bonus/player collision
			if (isCollided(bonus_pose, baseRadious*0.8, playerPose, player_diameter, 0.5*player_diameter, -0.5*player_diameter, 0))
			{
				playerLife++;
				bonus_timer[i] = 20;
			}
		}
	}
	
	glPopMatrix();
	glEnable(GL_FOG);
	isSky = 0;
	isBullet = 0;
	// end of bonus spheres draw





	// draw flag spheres : shows nearest abd farthest enemies' start point
	Sphere(0, 0, 0 - 3 - 0 + playerPose[2], baseRotateAngle * 6 * 1000, 0, 0, FireId, baseRadious *1.5, 50, 1, 1, 1, 1);
	Sphere(0, 0, 0 - 3 - 1 * num_of_enemies + playerPose[2], baseRotateAngle * 6 * 1000, 0, 0, FireId, baseRadious *1.5, 50, 1, 1, 1, 1);
	// end of flag spheres

	


	// draw enemy explosion
	
	for (int i = 0; i < num_of_enemies; i++)
	{
		float fire_color[4] = { 1.0, 1.0, 0, 0.3 };

		if (enemy_is_dead[i]>3)
		{
			float dist = enemiesBasePose*(2 + 1.5*cos(i));
			if ((dist - 3 - 2 * i + playerPose[2]) > (playerPose[2] + 15))
			{
				coeff = (dist - 3 - 2 * i + playerPose[2] - playerPose[2] - 15) / (num_of_enemies + 15 + 3);
				dist -= (coeff + 1)*(num_of_enemies + 15 + 3);
			}
			enemy_pose[0] = playerPose[0] * 0.8 + 2 * tan(i)*sin(i);
			enemy_pose[1] = playerPose[1] * 0.8 + 2 * tan(6 * i)*cos(50 * i);
			enemy_pose[2] = dist - 3 - i + playerPose[2];
			enemy_diameter = baseRadious *0.5*(4 + 3 * sin(3 * i));

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			fire_color[3] = 0.5*(enemy_is_dead[i] / 20);
			draw_shield(enemy_pose[0], enemy_pose[1], enemy_pose[2], fire_color, enemy_diameter*enemy_is_dead[i] / 10, FireId);

			
			int explosion_parts = 3 + 0.7 * (1.0f*enemy_is_dead[i] * rand() / RAND_MAX);
			for (int j = 0; j < explosion_parts; j++)
			{
				float explosion_radius = (1.0f*enemy_is_dead[i] * rand() / RAND_MAX / 20);

				float explosion_x = (1.0f*enemy_is_dead[i] * rand() / RAND_MAX / 20);
				float explosion_y = (1.0f*enemy_is_dead[i] * rand() / RAND_MAX / 20);
				float explosion_z = (1.0f*enemy_is_dead[i] * rand() / RAND_MAX / 20);

				float explosion_red = 0.8 + 0.2*(1.0f*enemy_is_dead[i] * rand() / RAND_MAX / 20);
				float explosion_green = 0.6 + 0.4*(1.0f*enemy_is_dead[i] * rand() / RAND_MAX / 20);
				float explosion_alpha = 0.1 + 0.9*(1.0f*enemy_is_dead[i] * rand() / RAND_MAX / 20);
				fire_color[0] = explosion_red;
				fire_color[1] = explosion_green;
				fire_color[3] = explosion_alpha;



				draw_shield(enemy_pose[0] + explosion_x - 0.5, enemy_pose[1] + -0.5, enemy_pose[2] + explosion_z - 0.5
					, fire_color, enemy_diameter*enemy_is_dead[i] * 0.3*explosion_radius, FireId);

				glPushMatrix();
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, FireId);
				glTranslatef(enemy_pose[0] + explosion_x - 0.5, enemy_pose[1] + -0.5, enemy_pose[2] + explosion_z - 0.5);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

				glColor4f(fire_color[0], fire_color[1], fire_color[2], fire_color[3]);
				glBegin(GL_TRIANGLES);

				//draw box front
				glNormal3f(0.0f, 0.0f, 1.0f);
				glTexCoord3f(0.0f, 0.0f, 0);
				glVertex3f(0.1f, 0.0f, 0.0f);

				glTexCoord3f(1.0f, 0.0f, 0);
				glVertex3f(-0.1f, 0.0f, 0.0f);


				float explosion_xx = enemy_is_dead[i] / 10 * sin(2 * Pi*(1.0f* rand() / RAND_MAX));
				float explosion_yy = enemy_is_dead[i] / 10 * sin(2 * Pi*(1.0f*rand() / RAND_MAX));
				float explosion_zz = enemy_diameter*enemy_is_dead[i] / 10 * sin(Pi*(1.0f* rand() / RAND_MAX));
				glTexCoord3f(1.0f, 1.0f, 0);
				glVertex3f(explosion_xx, explosion_yy, explosion_zz);


				glEnd();
				glPopMatrix();
			}
		}
	}
	
	// end of enemy explosion

	
	
	

	
	


	// draw player shield
	if (playerLife < 4)
	{
		shield_color[3] = 0;
	}

	if (playerLife > 3)
	{
		draw_shield(playerPose[0], playerPose[1] + 0.2, playerPose[2], shield_color, player_diameter, ShieldId);
		if (shield_timer)
			shield_timer--;
		if (shield_timer <= 0)
		{
			shield_timer = 0;
			shield_color[0] = 0;
			shield_color[1] = 1;
			shield_color[2] = 1;
			shield_color[3] = 0.2;
			if (playerLife < 4)
			{
				shield_color[3] = 0;
			}

		}
	}
	
	// end of draw player shield

	// player explosion
	float fire_color[4] = { 1.0, 1.0, 0, 0.3 };
	glDisable(GL_FOG);

	if (playerLife <= 0 )

	{
		float player_timer_alias = player_timer;
		if (!pause)
			player_timer--;
		if (player_timer == 0)
		{
			pause = 1;
			player_timer_alias = 10 + 15 * rand() / RAND_MAX;
			end_game = true;

		}

		fire_color[3] = 0.5 + 0.5*(player_timer_alias / 20);

		int explosion_parts = 3 + 0.7 * (1.0f * 3 * rand() / RAND_MAX);
		for (int j = 0; j < explosion_parts; j++)
		{
			float explosion_radius = 1;

			float explosion_x = (1.0f*player_timer_alias * rand() / RAND_MAX / 100);
			float explosion_y = (1.0f*player_timer_alias * rand() / RAND_MAX / 100);
			float explosion_z = (1.0f*player_timer_alias * rand() / RAND_MAX / 100);

			float explosion_red = 0.8 + 0.2*(1.0f*player_timer_alias * rand() / RAND_MAX / 100);
			float explosion_green = 0.6 + 0.4*(1.0f*player_timer_alias * rand() / RAND_MAX / 100);
			float explosion_alpha = 0.5 + 0.5*(1.0f*player_timer_alias * rand() / RAND_MAX / 100);
			fire_color[0] = explosion_red;
			fire_color[1] = explosion_green;
			fire_color[3] = explosion_alpha;



			draw_shield(playerPose[0] + explosion_x , playerPose[1] + explosion_y+0.1 , playerPose[2] + explosion_z 
				, fire_color, player_diameter*player_timer_alias/30 * 0.3*explosion_radius, FireId);

			glPushMatrix();
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, FireId);
			glTranslatef(playerPose[0] + explosion_x , playerPose[1] + explosion_y+0.1, playerPose[2] + explosion_z );
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			glColor4f(fire_color[0], fire_color[1], fire_color[2], fire_color[3]);
			glBegin(GL_TRIANGLES);

			//draw box front
			glNormal3f(0.0f, 0.0f, 1.0f);
			glTexCoord3f(0.0f, 0.0f, 0);
			glVertex3f(0.1f, 0.0f, 0.0f);

			glTexCoord3f(1.0f, 0.0f, 0);
			glVertex3f(-0.1f, 0.0f, 0.0f);


			float explosion_xx = player_timer_alias / 50 * sin(2 * Pi*(1.0f* rand() / RAND_MAX));
			float explosion_yy = player_timer_alias / 50 * sin(2 * Pi*(1.0f*rand() / RAND_MAX));
			float explosion_zz = enemy_diameter*player_timer_alias / 10 * sin(Pi*(1.0f* rand() / RAND_MAX));
			glTexCoord3f(1.0f, 1.0f, 0);
			glVertex3f(explosion_xx, explosion_yy, explosion_zz);


			glEnd();
			glPopMatrix();
		}
	}
	glEnable(GL_FOG);

	// end of player explosion

	
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glutSwapBuffers();	


}

void reshape_window(int w, int h)
{
	width = w;
	height = h;
	glViewport(0, 0, w, h);
	float AR = ((float)w) / h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.f, AR, 0.001f, 1000);
}


void timerFunc(int v)
{

	if (!pause)
	{
		enemiesBasePose += enemies_base_speed;
		baseRotateAngle += 1.0f / 1000.0f;
		
		playerPose[2] += player_speed;
		if (baseRotateAngle > 360.f)
		{
			baseRotateAngle -= 360;
		}
		

		//Advance the animation
		if (_model != NULL) {
			_model->advance(0.025f);
		}

		
	}
	glutPostRedisplay(); 

	glutTimerFunc(1000 / fps, timerFunc, v); 
}


void keysFunc(unsigned char key, int xx, int yy) {

	if (key == 27)
		exit(0);
	if (key == 'p' || key == 'P')
	{
		if (!end_game)
			pause = !pause;
	}
	else if (key == 'r' || key == 'R')
		reset();

		
	if (pause)
		return;
	switch (key)
	{
	case 27:
		exit(0);
		break;

	case 'r':
	case 'R':
		reset();
		break;

	case 'w':
	case 'W':
		if (playerLife)
		{
			bullet_idx++;
			bullet_idx = bullet_idx % (bullet_max - 1);
			bullet_set_flag[bullet_idx - 1] = 0;
			bullet_num += (bullet_num >= bullet_max) ? 0 : 1;
		}

		

		break;
	
	


	}
}

void arrowFunc(int key, int xx, int yy) {
	float fraction = 0.1f;
	if (!playerLife)
		return;
	switch (key) {
	case GLUT_KEY_UP: playerPoseFlag[1] = 1; break;
	case GLUT_KEY_DOWN: playerPoseFlag[1] = -1; break;
	case GLUT_KEY_RIGHT: playerPoseFlag[0] = 1; break;
	case GLUT_KEY_LEFT: playerPoseFlag[0] = -1; break;

	}
}

void arrowUpFunc(int key, int x, int y) {

	switch (key) {
	case GLUT_KEY_UP: playerPoseFlag[1] = 0; break;
	case GLUT_KEY_DOWN: playerPoseFlag[1] = 0; break;
	case GLUT_KEY_RIGHT: playerPoseFlag[0] = 0; break;
	case GLUT_KEY_LEFT: playerPoseFlag[0] = 0; break;

	}
}

void mousePassiveFunc(int x, int y) {

	if (x_prev == 0 || y_prev == 0)
	{
		x_prev = x;
		y_prev = y;
	}
	else
	{
		cameraPose[0] -= (x - x_prev)*0.02;
		cameraPose[1] += (y - y_prev)*0.02;
		x_prev = x;
		y_prev = y;
	}
}

void mouseFunc(int button, int state, int x, int y) {

	//

}

int main(int argc, char* argv[])
{
	glutInit(&argc, (char**)argv);
	
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(1366, 768);
	glutInitWindowPosition(0, 0);


	glutCreateWindow((const char*)"Space Chase");
	
	glutTimerFunc(5, timerFunc, fps); 
	glutReshapeFunc(reshape_window); 
	glutIgnoreKeyRepeat(1);
	glutKeyboardFunc(keysFunc);
	glutSpecialFunc(arrowFunc);
	glutSpecialUpFunc(arrowUpFunc);

	

	glutMouseFunc(mouseFunc);
	glutPassiveMotionFunc(mousePassiveFunc);

	glutDisplayFunc(render); 
	                                                                                                                

	init(); 

	glutMainLoop(); 

	return 0;
}