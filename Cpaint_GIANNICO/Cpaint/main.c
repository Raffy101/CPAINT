#include "../lib/libgraphique.h"
#include <stdio.h>
#include <math.h>
#include <string.h>

#define RESH 1000
#define RESV 600
#define OUTILH 100
#define OUTILV 600
#define BANDEH 800
#define BANDEV 25
#define LIGNEH 29
#define LIGNEV 600
#define RECTX 70
#define RECTY 90

void MENU();
void Init();
void Init2();

void bouton_ligne(Point p1, Point p2, Point *clic, int couleur);
void rectangle_vide(Point coin, Point p1, Point *clic, int couleur);
void rectangle_plein(Point coin, Point p1, Point *clic, int couleur);
void cercle_vide(Point centre, Point rayon, Point *clic, int couleur);
void disque(Point centre, Point rayon, Point *clic, int couleur);
void polygone_vide(Point *clic, int couleur);
void polygone_plein(Point *clic, int couleur);
void inserer_texte(Point *clic, int couleur);
void crayon(Point *clic, int couleur, int taille);
void gomme(Point *clic, int taille);
int choix_couleur(Point *clic);
char charger(char chemin_fichier[]);
void sauvegarder(SDL_Surface *source);
int choix_taille(Point *clic);
char sauv_undo(SDL_Surface *source, unsigned int *num);
void undo(char nom_image[], unsigned int *num);
void redo(char nom_image[], unsigned int *num, int numMax);
void clearAll(Point *clic);
int pipette(Point *clic);


/******************************************************************************/
/* 									MAIN                                      */
/******************************************************************************/

int main(int argc, char *argv[])
{

    // début de la session graphique
    ouvrir_fenetre(RESH,RESV);

	
	MENU();

	Point page_outils={0,0};
	Point bande={100,575};

	Point boutonLigne={0,0};
	Point rect_vide={0,30};
	Point rect_plein={0,60};
	Point cerc_vide={0,90};
	Point disq={0,120};
	Point poly={0,150};
	Point poly_plein={0,180};
	Point txt={0,210};
	Point cray={0,240};
	Point gom={0,270};
	Point bouton_couleur={0,300};
	Point pip={30,240};

	Point p1={0,0};
	Point p2={0,0};
	Point clic={0,0};

	int Couleur_def = noir;
	int taille_point = 1;

	char nom_undo[150];

	static unsigned int numUndo = 0;
	unsigned int *pointeurSurNumUndo = &numUndo;
	nom_undo[150] = sauv_undo(SDL_GetVideoSurface(), pointeurSurNumUndo);
		
	int numUndoMax=0;
	clic = attendre_clic();

	while(1)
	{

		if(clic.x >=29)
		{
			clic = attendre_clic();
		}
		
		while(clic.x <=29 && clic.y <=29)
		{	
			afficher_image("images/ligne_droite_allumer.bmp", boutonLigne);// Segment 
			afficher_texte(" ? Selectionner 2 points pour tracer une ligne.", 13, bande, noir);
			actualiser();
			bouton_ligne(p1, p2, &clic, Couleur_def);
			dessiner_rectangle(bande, BANDEH, BANDEV, blanc);
			actualiser();
			numUndo++;
			numUndoMax++;
			nom_undo[150] = sauv_undo(SDL_GetVideoSurface(), pointeurSurNumUndo);	//Sauvegarder une action
		}

		
		while(clic.x <=29 && (clic.y >=30 && clic.y<= 59))//Rectangle_vide
		{	
			afficher_image("images/rectangle_vide_allumer.bmp", rect_vide);
			afficher_texte(" ? Selectionner 2 points pour tracer un rectangle vide.", 13, bande, noir);
			actualiser();
			rectangle_vide(p1, p2, &clic, Couleur_def);	
			dessiner_rectangle(bande, BANDEH, BANDEV, blanc);
			actualiser();
			numUndo++;
			numUndoMax++;
			nom_undo[150] = sauv_undo(SDL_GetVideoSurface(), pointeurSurNumUndo);
		}
		
		while(clic.x <=29 && (clic.y >=60 && clic.y<= 89))//Rectangle plein
		{	
			afficher_image("images/rectangle_plein_allumer.bmp", rect_plein);
			afficher_texte(" ? Selectionner 2 points pour tracer un rectangle plein.", 13, bande, noir);
			actualiser();
			rectangle_plein(p1, p2, &clic, Couleur_def);
			dessiner_rectangle(bande, BANDEH, BANDEV, blanc);	
			actualiser();
			numUndo++;
			numUndoMax++;
			nom_undo[150] = sauv_undo(SDL_GetVideoSurface(), pointeurSurNumUndo);
		}


		while(clic.x <=29 && (clic.y >=90 && clic.y<= 119))//Cercle_vide
		{	
			afficher_image("images/cercle_vide_allumer.bmp", cerc_vide);
			afficher_texte(" ? Selectionner 2 points pour tracer un cercle vide.", 13, bande, noir);
			actualiser();
			cercle_vide(p1, p2, &clic, Couleur_def);
			dessiner_rectangle(bande, BANDEH, BANDEV, blanc);	
			actualiser();
			numUndo++;
			numUndoMax++;
			nom_undo[150] = sauv_undo(SDL_GetVideoSurface(), pointeurSurNumUndo);
		}


		while(clic.x <=29 && (clic.y >=120 && clic.y<= 149))//Disque
		{	
			afficher_image("images/disque_allumer.bmp", disq);
			afficher_texte(" ? Selectionner 2 points pour tracer un cercle plein.", 13, bande, noir);
			actualiser();
			disque(p1, p2, &clic, Couleur_def);
			dessiner_rectangle(bande, BANDEH, BANDEV, blanc);	
			actualiser();
			numUndo++;
			numUndoMax++;
			nom_undo[150] = sauv_undo(SDL_GetVideoSurface(), pointeurSurNumUndo);
		}


		while(clic.x <=29 && (clic.y >=150 && clic.y<= 179))//Polygone 
		{
			afficher_image("images/polygone_allumer.bmp", poly);
			afficher_texte(" ? Selectionner des points pour tracer un polygone et ensuite faites un clic droit pour fermer le polygone.", 13, bande, noir);
			actualiser();
			polygone_vide(&clic, Couleur_def);
			dessiner_rectangle(bande, BANDEH, BANDEV, blanc);	
			actualiser();
			numUndo++;
			numUndoMax++;
			nom_undo[150] = sauv_undo(SDL_GetVideoSurface(), pointeurSurNumUndo);
		}

		while(clic.x <=29 && (clic.y >=180 && clic.y<= 209))//Polygone plein
		{	
			afficher_image("images/polygone_plein_allumer.bmp", poly_plein);
			afficher_texte(" ? Selectionner des points pour tracer un polygone et ensuite faites un clic droit pour fermer le polygone.", 13, bande, noir);
			actualiser();
			polygone_plein(&clic, Couleur_def);
			dessiner_rectangle(bande, BANDEH, BANDEV, blanc);	
			actualiser();
			numUndo++;
			numUndoMax++;
			nom_undo[150] = sauv_undo(SDL_GetVideoSurface(), pointeurSurNumUndo);
		}

		if(clic.x <=29 && (clic.y >=210 && clic.y<= 239))//Inserer texte
		{	
			afficher_image("images/texte_allumer.bmp", txt);
			afficher_texte(" ? Selectionner un point pour ecrire puis choisissez la taille de votre texte.", 13, bande, noir);
			actualiser();
			inserer_texte(&clic, Couleur_def);
			dessiner_rectangle(bande, BANDEH, BANDEV, blanc); 
			actualiser();
			numUndo++;
			numUndoMax++;
			nom_undo[150] = sauv_undo(SDL_GetVideoSurface(), pointeurSurNumUndo);
		}
	
		if(clic.x <=29 && (clic.y >=240 && clic.y<= 269))//Crayon
		{
			afficher_image("images/crayon_allumer.bmp", cray);
			afficher_texte(" ? Faites un clic gauche pour commencer a dessiner et un autre pour arreter.", 13, bande, noir);
			actualiser();

		
			while(clic.x <=29 && (clic.y >=240 && clic.y<= 269))
			{	
				crayon(&clic, Couleur_def, taille_point);
				actualiser();
			}

			numUndo++;
			numUndoMax++;
			nom_undo[150] = sauv_undo(SDL_GetVideoSurface(), pointeurSurNumUndo);
		}

		if(clic.x <=29 && (clic.y >=270 && clic.y<= 299))//Gomme
		{
			afficher_texte(" ? Faites un clic gauche pour commencer a effacer et un autre pour arreter.", 13, bande, noir);
			afficher_image("images/gomme_allumer.bmp", gom);
			actualiser();

			while(clic.x <=29 && (clic.y >=270 && clic.y<= 299))
			{	
				gomme(&clic,taille_point);
				actualiser();  
			}

			numUndo++;
			numUndoMax++;
			nom_undo[150] = sauv_undo(SDL_GetVideoSurface(), pointeurSurNumUndo);

		}

		if(clic.x <=29 && (clic.y >=300 && clic.y<= 329))//Choix Couleur
		{	
			Point rect_gris={29,300};
			Point rect_gris2={0,329};
			afficher_image("images/choix_couleur2.bmp", bouton_couleur);
			afficher_texte(" ? Choisissez une couleur ou cliquez sur le bouton arc-en-ciel pour creer une couleur.", 13, bande, noir); 
			actualiser(); 

			Couleur_def = choix_couleur(&clic);
		
			dessiner_rectangle(rect_gris,RECTX, RECTY, gris);
			dessiner_rectangle(rect_gris2, 40, 50, gris);
			dessiner_rectangle(bande, BANDEH, BANDEV, blanc);
			actualiser();
			 
		}

		if((clic.x >= 5 && clic.x <= 25) && (clic.y >=352 && clic.y<= 372))//Sinon si on choisi la couleur violet ca bug
		{
			//printf("VIOLET\n");	 
			clic = attendre_clic();
		}

		if((clic.x >=35 && clic.x <=60) && (clic.y >=26 && clic.y<= 45))//clear
		{
			clearAll(&clic);
			numUndo++;
			numUndoMax++;
			nom_undo[150] = sauv_undo(SDL_GetVideoSurface(), pointeurSurNumUndo);
		}
			
		if((clic.x >=35 && clic.x <=60) && (clic.y >=0 && clic.y<= 25))//Sauvegarder
		{
			dessiner_rectangle(page_outils, OUTILH, OUTILV, blanc);
			actualiser();
			sauvegarder(SDL_GetVideoSurface());
		}
		
		if((clic.x >=57 && clic.x <=76) && (clic.y >=0 && clic.y<= 25))//UNDO
		{
			undo(nom_undo, &numUndo);
			actualiser();
		}
		if((clic.x >=77 && clic.x <=97) && (clic.y >=0 && clic.y<= 25))//REDO
		{
			redo(nom_undo, &numUndo, numUndoMax);
			actualiser();
		}

		while((clic.x >=13 && clic.x <=83) && (clic.y >=390 && clic.y<=402 ))//Choisir la Taille du Point
		{
			taille_point = choix_taille(&clic);
		}

		while((clic.x >=30 && clic.x <= 59) && (clic.y >=240 && clic.y<= 269)) // pipette
		{
			afficher_image("images/pipette_allumer.bmp", pip);
			afficher_texte(" ? Cliquez sur un pixel pour copier une couleur", 13, bande, noir); 
			actualiser();
			Couleur_def = pipette(&clic);
			
		}

		
	}
    // fin de la session graphique
	system("rm UNDO/*");	//Supprime les images UNDO.
    fermer_fenetre();
    return 0;
}

/*******************************************************************************************************/
/*												MENU					   							   */
/*******************************************************************************************************/

void MENU()
{
	char fichierCharger[200];

	system("rm UNDO/*");

	Point Emplacement_fic_charger;
	Point menu={0,0};
	Point debut={0,0};
	//Point new={693,250};
	//Point load={693,306};
	afficher_image("images/MENU.bmp", menu);
	actualiser();
	
	//dessiner_rectangle(new, 260, 35, bleu);
	//actualiser();
	while(!(menu.x >= 693 && menu.x <= 953 && menu.y >= 250 && menu.y <= 285))
	{	
		menu = attendre_clic();
		if((menu.x >= 693 && menu.x <= 953 && menu.y >= 250 && menu.y <= 285))
		{
			afficher_image("images/nouveau.bmp", debut);
			actualiser();
			attente(500);
		}
		
		if (menu.x >= 693 && menu.x <= 953 && menu.y >= 305 && menu.y <= 340)
		{
			afficher_image("images/charger.bmp", debut);
			actualiser();
			attente(100);
			fichierCharger[200] = charger(fichierCharger);

			SDL_Surface *ecran = SDL_LoadBMP(fichierCharger);
			if(ecran->w >= RESH)			//Si grande image afficher en 0,0 
			{
				Emplacement_fic_charger.x=0;		
				Emplacement_fic_charger.y=0;
			}
			else							//Sinon si petite image afficher en 101,0 
			{
				Emplacement_fic_charger.x=101;
				Emplacement_fic_charger.y=0;
			}
			break;

		}

	}

	/****************** Page Blanche ******************/

	Point page_blanche={0,0};
	dessiner_rectangle(page_blanche, RESH, RESV, blanc);
	
	/**************************************************/

	/****************** Page Outils *******************/

	afficher_image(fichierCharger, Emplacement_fic_charger);
	Init();
}

/*******************************************************************************************************/
/*									   	  Initialisation					   					  	   */
/*******************************************************************************************************/

void Init()
{
	Point page_outils={0,0};
	Point boutonLigne={0,0};
	Point rect_vide={0,30};
	Point rect_plein={0,60};
	Point cerc_vide={0,90};
	Point disq={0,120};
	Point poly={0,150};
	Point poly_plein={0,180};
	Point txt={0,210};
	Point cray={0,240};
	Point gom={0,270};
	Point color={0,300};
	Point save={35,1};
	Point glissiere={13,390};
	Point glissiere2={13,390};
	Point undo={57,1};
	Point redo={77,1};
	Point new={35,26};
	Point pip={30,240};

	dessiner_rectangle(page_outils, OUTILH, OUTILV, gris);
	afficher_image("images/ligne_droite.bmp", boutonLigne);
	afficher_image("images/rectangle_vide.bmp", rect_vide);
	afficher_image("images/rectangle_plein.bmp", rect_plein);
	afficher_image("images/cercle_vide.bmp", cerc_vide);
	afficher_image("images/disque.bmp", disq);
	afficher_image("images/polygone.bmp", poly);
	afficher_image("images/polygone_plein.bmp", poly_plein);
	afficher_image("images/texte.bmp", txt);
	afficher_image("images/crayon.bmp", cray);
	afficher_image("images/gomme.bmp", gom);
	afficher_image("images/couleur.bmp", color);
	afficher_image("images/save_icon.bmp", save);
	afficher_image("images/glissiere2.bmp", glissiere2);
	afficher_image("images/glissiere.bmp", glissiere);
	afficher_image("images/undo.bmp", undo);
	afficher_image("images/redo.bmp", redo);
	afficher_image("images/new.bmp", new);
	afficher_image("images/pipette.bmp", pip);
	actualiser();

}

void Init2()
{
	Point boutonLigne={0,0};
	Point rect_vide={0,30};
	Point rect_plein={0,60};
	Point cerc_vide={0,90};
	Point disq={0,120};
	Point poly={0,150};
	Point poly_plein={0,180};
	Point txt={0,210};
	Point cray={0,240};
	Point gom={0,270};
	Point save={35,1};
	Point undo={57,1};
	Point redo={77,1};
	Point new={35,26};
	Point pip={30,240};

	afficher_image("images/ligne_droite.bmp", boutonLigne);
	afficher_image("images/rectangle_vide.bmp", rect_vide);
	afficher_image("images/rectangle_plein.bmp", rect_plein);
	afficher_image("images/cercle_vide.bmp", cerc_vide);
	afficher_image("images/disque.bmp", disq);
	afficher_image("images/polygone.bmp", poly);
	afficher_image("images/polygone_plein.bmp", poly_plein);
	afficher_image("images/texte.bmp", txt);
	afficher_image("images/crayon.bmp", cray);
	afficher_image("images/gomme.bmp", gom);
	afficher_image("images/save_icon.bmp", save);
	afficher_image("images/undo.bmp", undo);
	afficher_image("images/redo.bmp", redo);
	afficher_image("images/new.bmp", new);
	afficher_image("images/pipette.bmp", pip);
	actualiser();

}

/*******************************************************************************************************/
/*												Ligne					   							   */
/*******************************************************************************************************/

void bouton_ligne(Point p1, Point p2, Point *clic, int couleur)
{
	Point boutonLigne={0,0};
	p1 = attendre_clic();

	if(p1.x >= OUTILH)
	{
		p2 = attendre_clic();
	}
	else
	{
		*clic = p1;
		afficher_image("images/ligne_droite.bmp", boutonLigne);
	}
	if(p1.x >= OUTILH && p2.x >= OUTILH)
	{
		dessiner_ligne(p1, p2, couleur);
	}
		
}

/*******************************************************************************************************/
/*											Rectangle vide			   								   */
/*******************************************************************************************************/

void rectangle_vide(Point coin, Point p1, Point *clic, int couleur)
{
	Point rect_vide={0,30};
	
	Point p2={0,0};
	Point p3={0,0};

	coin = attendre_clic();
	
	if(coin.x >= OUTILH)
	{
		p1 = attendre_clic();
	}
	else
	{
		*clic = coin;
		afficher_image("images/rectangle_vide.bmp", rect_vide);
	}
		p2.y = p1.y;
		p2.x = coin.x;

		
		p3.x = p1.x;
		p3.y = coin.y;

	if(coin.x >= OUTILH)
	{	
		dessiner_ligne(coin, p2, couleur);
		dessiner_ligne(p2, p1, couleur);
		dessiner_ligne(coin, p3, couleur);
		dessiner_ligne(p3, p1, couleur);
	}
	
}

/*******************************************************************************************************/
/*											Rectangle Plein			   								   */
/*******************************************************************************************************/

void rectangle_plein(Point coin, Point p1, Point *clic, int couleur)
{
	Point rect_plein={0,60};
	
	coin = attendre_clic();
	
	if(coin.x >= OUTILH)
	{
		p1 = attendre_clic();
	}
	else
	{
		*clic = coin;
		afficher_image("images/rectangle_plein.bmp", rect_plein);
	}

	p1.x = p1.x - coin.x;
	p1.y = p1.y - coin.y;
	
	if(coin.x >= OUTILH)
	{	
		dessiner_rectangle(coin, p1.x, p1.y, couleur);
	}
	
}

/*******************************************************************************************************/
/*											Cercle vide			   								 	   */
/*******************************************************************************************************/

void cercle_vide(Point centre, Point rayon, Point *clic, int couleur)
{
	Point cerc_vide={0,90};

	centre = attendre_clic();

	int rayonX;
	int rayonY;
	int rayonFinal;

	if(centre.x >= OUTILH)
	{
		rayon = attendre_clic();
	}
	else
	{
		*clic = centre;
		afficher_image("images/cercle_vide.bmp", cerc_vide);
	}
		
		rayonX = (rayon.x - centre.x) * (rayon.x - centre.x);	//Calcul (Pythagore) pour trouver le 2ème clic qui définit la taille du cercle.
		rayonY = (rayon.y - centre.y) * (rayon.y - centre.y);
		rayonFinal = sqrt(rayonX + rayonY);
		
	
	
	if(centre.x >= OUTILH)
	{	
		dessiner_cercle(centre, rayonFinal, couleur);
	}
	

}

/*******************************************************************************************************/
/*												Disque					   							   */
/*******************************************************************************************************/


void disque(Point centre, Point rayon, Point *clic, int couleur)
{
	Point disq={0,120};

	centre = attendre_clic();

	int rayonX;
	int rayonY;
	int rayonFinal;

	if(centre.x >= OUTILH)
	{
		rayon = attendre_clic();
	}
	else
	{
		*clic = centre;
		afficher_image("images/disque.bmp", disq);
	}

		rayonX = (rayon.x - centre.x) * (rayon.x - centre.x);	// Calcul (Pythagore) pour trouver le 2ème clic qui définit la taille du cercle.
		rayonY = (rayon.y - centre.y) * (rayon.y - centre.y);
		rayonFinal = sqrt(rayonX + rayonY);
	
	if(centre.x >= OUTILH)
	{	
		dessiner_disque(centre, rayonFinal, couleur);
	}	

	
}

/*******************************************************************************************************/
/*											Polygone vide			   								   */
/*******************************************************************************************************/


void polygone_vide(Point *clic, int couleur)
{	
	Point poly={0,150};

	int i=0;
	int n=0;
	Point polygone [100];
	Point secondPoint [100];
	
	polygone[0]=attendre_clic();
	
	if(polygone[0].x >= OUTILH)
	{
		Point premierPoint=polygone[0];

		while(i==n)
		{
			secondPoint[n]=attendre_clic_gauche_droite();
			
			if(secondPoint[n].x >= 0 && secondPoint[n].y >= 0)
			{
				if(secondPoint[n].x >= OUTILH)
				{
					dessiner_ligne(polygone[0],secondPoint[n],couleur);
					polygone[0]=secondPoint[n];
					actualiser();
					i++;
					n++;
				}

			}

			else
			{
				dessiner_ligne(polygone[0],premierPoint,couleur);
				actualiser();
				i=0;
			}

			

		}		

	}

	else 
	{
		*clic=polygone[0];	
		afficher_image("images/polygone.bmp", poly);	
	}	

}

/*******************************************************************************************************/
/*											Polygone Plein			   								   */
/*******************************************************************************************************/



void polygone_plein(Point *clic, int couleur)
{
	Point poly_plein={0,180};	
	
	int i=0;
	int n=0;
	Point polygone [100];
	Point secondPoint [100];
	
	polygone[0]=attendre_clic();
	
	if(polygone[0].x >= OUTILH)
	{
		Point premierPoint=polygone[0];

		while(i==n)
		{
			secondPoint[n]=attendre_clic_gauche_droite();
			
			if(secondPoint[n].x >= 0 && secondPoint[n].y >= 0)
			{
				if(secondPoint[n].x >= OUTILH)
				{
					dessiner_ligne(polygone[0],secondPoint[n],couleur);
					polygone[0]=secondPoint[n];
					actualiser();
					i++;
					n++;
				}

			}

			else
			{
				dessiner_ligne(polygone[0],premierPoint,couleur);
				actualiser();
				i=0;
			}


		}	


	}

	else 
	{
		*clic=polygone[0];
		afficher_image("images/polygone_plein.bmp", poly_plein);		
	}	

	
}


/*******************************************************************************************************/
/*										 Inserer un texte		    							       */
/*******************************************************************************************************/


void inserer_texte(Point *clic, int couleur)
	{
		Point bouton_txt={0,210};
		
		char texte[100];
		int tailleTexte = 0;
		Point emplacementImage = attendre_clic();

		
		if(emplacementImage.x >= OUTILH)
		{		
			printf("Entrez votre texte :\n");
			scanf("%s", texte);

			printf("Entrez la taille de votre texte :\n");
			scanf("%d", &tailleTexte);

			afficher_texte(texte, tailleTexte, emplacementImage, couleur);
		}
		else
		{
			*clic = emplacementImage;
			afficher_image("images/texte.bmp", bouton_txt);
			
		}

	}

/*******************************************************************************************************/
/*												Crayon			   									   */
/*******************************************************************************************************/

void crayon(Point *clic, int couleur, int taille)
	{
		Point cray={0,240};

		Point centre={0,0};
		Point clic_gauche={300,0};	
		Point clic_gauche2={101,0};
		Point clic_avant={0,0};

		Point bande={100,575};

		traiter_evenements();
			
		clic_gauche = clic_a_eu_lieu();		
		clic_avant=clic_gauche;

		while(clic_gauche.x != -1 && clic_gauche.y != -1)
			{
				dessiner_rectangle(bande, BANDEH, BANDEV, blanc);
				actualiser();

				if(clic_gauche.x <= OUTILH )
				{
					*clic = clic_gauche;
					afficher_image("images/crayon.bmp", cray);	
					break;
				}
				centre=deplacement_souris_a_eu_lieu();

				if(centre.x >= OUTILH)
				{	
					if(taille == 1)
					{
						dessiner_ligne(centre,clic_avant, couleur);

					}
					else
					{
						dessiner_disque(centre, taille, couleur);
					}
					actualiser();
					

				}	

				clic_avant=centre;

				reinitialiser_evenements();
				
		/**************************** 2ème clic pour arreter de dessiner ************************/

				traiter_evenements();

				clic_gauche2 = clic_a_eu_lieu();

				
				if(clic_gauche2.x != -1 && clic_gauche2.y != -1)
				{	
					clic_gauche.x = 30;
					clic_gauche.y = -1;
				}
					
				reinitialiser_evenements();
				
			}		
				
		
		if(clic_gauche2.x <= OUTILH )
		{
			*clic = clic_gauche2;
			afficher_image("images/crayon.bmp", cray);	
		}
		
		/***************************************************************************************/


	}



/*******************************************************************************************************/
/*												Gomme			   									   */
/*******************************************************************************************************/

void gomme(Point *clic, int taille)
	{	
		Point gom={0,270};
	
		Point centre={0,0};
		Point clic_gauche={300,0};	
		Point clic_gauche2={101,0};
		
		Point bande={100,575};

		traiter_evenements();
			
		clic_gauche = clic_a_eu_lieu();		

		while(clic_gauche.x != -1 && clic_gauche.y != -1)
			{
				dessiner_rectangle(bande, BANDEH, BANDEV, blanc);
				actualiser();

				
				if(clic_gauche.x <= OUTILH )
				{
					*clic = clic_gauche;
					afficher_image("images/gomme.bmp", gom);	
					break;
				}
				centre=deplacement_souris_a_eu_lieu();
				

				if(centre.x >= OUTILH)
				{	
					dessiner_disque(centre, taille, blanc);
					actualiser();
					
				}	
			

		/**************************** 2ème clic pour arreter de dessiner ************************/
				traiter_evenements();
				clic_gauche2 = clic_a_eu_lieu();


				if(clic_gauche2.x != -1 && clic_gauche2.y != -1)
				{	
					clic_gauche.x = 30;
					clic_gauche.y = -1;
				}
					 
				reinitialiser_evenements();
				
			}		
				
		
		if(clic_gauche2.x <= OUTILH )
		{
			*clic = clic_gauche2;
			afficher_image("images/gomme.bmp", gom);	
		}
		
		/***************************************************************************************/
	}


/*******************************************************************************************************/
/*										Le choix des couleurs		   							  	   */
/*******************************************************************************************************/


int choix_couleur(Point *clic)
	{
		int R = 0, G = 0, B = 0;

		Point bouton_couleur={0,300};
		Point choix_clic={0,0};
		Point rect_gris={29,300};
		Point rect_gris2={0,329};
		
		choix_clic = attendre_clic();
		

		if((choix_clic.x >= 5 && choix_clic.x <= 25) && (choix_clic.y >=304 && choix_clic.y<= 324))
		{
			afficher_image("images/couleurs/noir.bmp", bouton_couleur);
			actualiser();
			*clic = rect_gris;
			dessiner_rectangle(rect_gris,RECTX, RECTY, gris);
			dessiner_rectangle(rect_gris2, 40, 50, gris);
			actualiser();
			return noir;
		}
		else if((choix_clic.x >= 27 && choix_clic.x <= 47) && (choix_clic.y >=304 && choix_clic.y<= 324))
		{
			afficher_image("images/couleurs/gris.bmp", bouton_couleur);
			actualiser();
			*clic = choix_clic;
			return gris;
		}
		else if((choix_clic.x >= 49 && choix_clic.x <= 69) && (choix_clic.y >=304 && choix_clic.y<= 324))
		{
			afficher_image("images/couleurs/blanc.bmp", bouton_couleur);
			actualiser();
			*clic = choix_clic;
			return blanc;
		}
		else if((choix_clic.x >= 71 && choix_clic.x <= 91) && (choix_clic.y >=304 && choix_clic.y<= 324))
		{
			afficher_image("images/couleurs/rouge.bmp", bouton_couleur);
			actualiser();
			*clic = choix_clic;
			return rouge;
		}
		else if((choix_clic.x >= 5 && choix_clic.x <= 25) && (choix_clic.y >=328 && choix_clic.y<= 348))
		{
			
			afficher_image("images/couleurs/orange.bmp", bouton_couleur);
			actualiser();
			*clic = rect_gris;
			return orange;
		}
		else if((choix_clic.x >= 27 && choix_clic.x <= 47) && (choix_clic.y >=328 && choix_clic.y<= 348))
		{
			afficher_image("images/couleurs/jaune.bmp", bouton_couleur);
			actualiser();
			*clic = choix_clic;
			return jaune;
		}
		else if((choix_clic.x >= 49 && choix_clic.x <= 69) && (choix_clic.y >=328 && choix_clic.y<= 348))
		{
			afficher_image("images/couleurs/vert.bmp", bouton_couleur);
			actualiser();
			*clic = choix_clic;
			return vert;
		}
		else if((choix_clic.x >= 71 && choix_clic.x <= 91) && (choix_clic.y >=328 && choix_clic.y<= 348))
		{
			afficher_image("images/couleurs/bleu.bmp", bouton_couleur);
			actualiser();
			*clic = choix_clic;
			return bleu;
		}
		else if((choix_clic.x >= 5 && choix_clic.x <= 25) && (choix_clic.y >=352 && choix_clic.y<= 372))
		{
			afficher_image("images/couleurs/violet.bmp", bouton_couleur);
			actualiser();
			*clic = choix_clic;
			return violet;
		}
		else if((choix_clic.x >= 27 && choix_clic.x <= 47) && (choix_clic.y >=352 && choix_clic.y<= 372))
		{
			afficher_image("images/couleurs/rose.bmp", bouton_couleur);
			actualiser();
			*clic = choix_clic;
			return magenta;
		}
		else if((choix_clic.x >= 49 && choix_clic.x <= 69) && (choix_clic.y >=352 && choix_clic.y<= 372))
		{
			afficher_image("images/couleurs/marron.bmp", bouton_couleur);
			actualiser();
			*clic = choix_clic;
			return marron;
		}
		else if((choix_clic.x >= 71 && choix_clic.x <= 91) && (choix_clic.y >=352 && choix_clic.y<= 372))
		{
			afficher_image("images/couleur.bmp", bouton_couleur);
			dessiner_rectangle(rect_gris,RECTX, RECTY, gris);
			dessiner_rectangle(rect_gris2, 40, 50, gris);
			actualiser();

			printf("Entrez des valeurs de 0 a 255 pour RGB\n");
			printf("Pour R:\n");
			scanf("%d", &R);
			printf("Pour G:\n");
			scanf("%d", &G);
			printf("Pour B:\n");
			scanf("%d", &B);
			
			
			*clic = choix_clic;
			
			return fabrique_couleur(R, G, B);
		}

		else
		{
			afficher_image("images/couleur.bmp", bouton_couleur);
			dessiner_rectangle(rect_gris,RECTX, RECTY, gris);
			dessiner_rectangle(rect_gris2, 40, 50, gris);

			actualiser();
		}
		
		*clic = attendre_clic();	

		return noir;

	}

/*******************************************************************************************************/
/*										Charger une Image	 										   */
/*******************************************************************************************************/


char charger(char chemin_fichier[])
	{

		printf("Entrez le chemin ou se trouve le fichier :\n");
		scanf("%s", chemin_fichier);
		
			
		return chemin_fichier[200];
	}


/*******************************************************************************************************/
/*									Sauvegarder une image		   									   */
/*******************************************************************************************************/


void sauvegarder( SDL_Surface *source)
	{
		char nom_image[150];
		int ca_a_marcher;

		printf("Comment voulez-vous appeler le fichier.bmp\n");
		scanf("%s",nom_image);

		ca_a_marcher = SDL_SaveBMP(source,nom_image);

		if(ca_a_marcher == 0)
			printf("Le fichier a ete sauvegarder !\n");
		else
			printf("Erreur 404 !\n");

		Init();
	}


/*******************************************************************************************************/
/*										Choisir la taille du point	 								   */
/*******************************************************************************************************/


int choix_taille(Point *clic)
{
	Point glissiere2={13,390};
	Point rectgris={13,394};
	int deplacement=0;
		
	Point clic_gauche={0,0};
	Point clic_gauche2={-1,-1};
	int taille = taille;

	traiter_evenements();
			
	clic_gauche = clic_a_eu_lieu();		//1er clic pour commencer


	while((clic_gauche.x >=13 && clic_gauche.x <=83) && (clic_gauche.y >=390 && clic_gauche.y<=402 ))
	{

		/**************** Faire glisser le curseur *****************/

		deplacement=deplacement_souris_a_eu_lieu().x;
				
		if(deplacement >=13 && deplacement <=71)
		{	
	
			Point glissiere={deplacement,390};

			afficher_image("images/glissiere2.bmp", glissiere2);
			afficher_image("images/glissiere.bmp", glissiere);
			dessiner_rectangle(rectgris, 70, 12, gris);
			afficher_image("images/glissiere.bmp", glissiere);
			actualiser();

					
			taille = deplacement-12;
				
		}

		/**********************************************************/

		traiter_evenements();

		clic_gauche2 = clic_a_eu_lieu(); //2eme clic pour terminer


		if((clic_gauche2.x != -1 && clic_gauche2.y != -1))
		{	
			*clic = attendre_clic();
			break;
		}

		reinitialiser_evenements();
				
	}		
				

	return taille;
}

/*******************************************************************************************************/
/*										Sauvegarder une action 										   */
/*******************************************************************************************************/

char sauv_undo(SDL_Surface *source, unsigned int *num)
{
	char nom_image[150];

	sprintf(nom_image, "UNDO/UNDO%d.bmp", *num); //créer plusieur image "UNDO" de nom different
	
	if(*num != 0)
		Init2();

	if(*num >=0)
		SDL_SaveBMP(source,nom_image);
	else
		printf("on ne peut plus: (UNDO< 0) !\n");
	
	return nom_image[150];
}

/*******************************************************************************************************/
/*											 	  UNDO 												   */
/*******************************************************************************************************/

void undo(char nom_image[], unsigned int *num)
{
	if(*num >0)
		*num = *num-1;	//Pour changer d'image et donc créer un "UNDO"
	else
		printf("Erreur < 0 !\n");

	Point debut={0,0};

	sprintf(nom_image, "UNDO/UNDO%d.bmp", *num);

	afficher_image(nom_image, debut);
	actualiser();
}

/*******************************************************************************************************/
/*											 	  REDO 												   */
/*******************************************************************************************************/

void redo(char nom_image[], unsigned int *num, int numMax)
{

	if(*num < numMax)
		*num = *num+1; //Pour changer d'image et donc créer un "REDO"
	else
	{
		printf("Erreur: > num !\n");
	}

	Point debut={0,0};


	sprintf(nom_image, "UNDO/UNDO%d.bmp", *num);
	
	afficher_image(nom_image, debut);
	actualiser();

}

/*******************************************************************************************************/
/*											 Clear All 												   */
/*******************************************************************************************************/

void clearAll(Point *clic)
	{
		Point page_blanche={101,0};
		dessiner_rectangle(page_blanche, RESH, RESV, blanc);
		actualiser();

	}

/*******************************************************************************************************/
/*											 Pipette												   */
/*******************************************************************************************************/

int pipette(Point *clic)
	{
		Point pip={30,240};
		Point bouton_couleur={0,300};

		Point pix= attendre_clic();
		int Couleur;

		if((clic->x >=30 && clic->x <= 59) && (clic->y >=240 && clic->y<= 269))
		{
			Couleur = couleur_point(pix);
		}
		else
		{
			*clic=pix;
			afficher_image("images/pipette.bmp", pip);
			afficher_image("images/couleur.bmp", bouton_couleur);
			actualiser();
		}

		
		afficher_image("images/pipette.bmp", pip);
		afficher_image("images/couleur.bmp", bouton_couleur);
		actualiser();

		*clic= attendre_clic();

		return Couleur;
	}	



























