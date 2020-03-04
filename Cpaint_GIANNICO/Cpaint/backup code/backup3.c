#include "../lib/libgraphique.h"
#include <stdio.h>
#include <math.h>


#define RESH 1000
#define RESV 600
#define OUTILH 100
#define OUTILV 600
#define BANDEH 800
#define BANDEV 25
#define LIGNEH 29
#define LIGNEV 600

void bouton_ligne(Point p1, Point p2, Point *clic, int couleur);
void rectangle_vide(Point coin, Point p1, Point *clic, int couleur);
void rectangle_plein(Point coin, Point p1, Point *clic, int couleur);
void cercle_vide(Point centre, Point rayon, Point *clic, int couleur);
void disque(Point centre, Point rayon, Point *clic, int couleur);
void polygone_vide(Point *clic, int couleur);
void polygone_plein(Point *clic, int couleur);
void inserer_texte(Point *clic, int couleur);
void crayon(Point *clic, int couleur);
void gomme(Point *clic);
int choix_couleur(Point *clic);
char charger(char chemin_fichier[]);
void sauvegarder( SDL_Surface *source);
//void clearAll(Point *clic);


int main(int argc, char *argv[]){

    // début de la session graphique
    ouvrir_fenetre(RESH,RESV);
	
	Point menu={0,0};
	Point debut={0,0};
	//Point new={504,250};
//	Point load={504,305};
	afficher_image("images/MENU.bmp", menu);
	actualiser();
	
	char fichierCharger[200];
//dessiner_rectangle(load, 260, 35, bleu);
//	actualiser();
	while(!(menu.x >= 504 && menu.x <= 765 && menu.y >= 250 && menu.y <= 285))
	{	
		menu = attendre_clic();
		if((menu.x >= 504 && menu.x <= 765 && menu.y >= 250 && menu.y <= 285))
		{
			afficher_image("images/nouveau.bmp", debut);
			actualiser();
			attente(500);
		}
		
		if (menu.x >= 504 && menu.x <= 765 && menu.y >= 305 && menu.y <= 340)
		{
			afficher_image("images/charger.bmp", debut);
			actualiser();
			attente(100);
			fichierCharger[200] = charger(fichierCharger);
			break;
		}

	}

	Point page_blanche={0,0};
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
	Point color={0,300};
	Point save={35,1};
	
	Point p1={0,0};
	Point p2={0,0};
	Point clic={0,0};
	Point Emplacement_fic_charger={200,200};

	int Couleur_def =  0xFFFF00;
	

	//****************** Page Blanche *******************

	dessiner_rectangle(page_blanche, RESH, RESV, blanc);
	
	//***************************************************

	//****************** Page Outils ********************

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
	afficher_image(fichierCharger, Emplacement_fic_charger);
	actualiser();
	//***************************************************

	
		
	clic = attendre_clic();

	while(1)
	{
		if(clic.x >=29)
		{
			clic = attendre_clic();
		}
		
		while(clic.x <=29 && clic.y <=29)
		{	
			afficher_image("images/ligne_droite_allumer.bmp", boutonLigne);// segment 
			afficher_texte("? Selectionner 2 points pour tracer une ligne.", 13, bande, noir);
			actualiser();
			bouton_ligne(p1, p2, &clic, Couleur_def);
			dessiner_rectangle(bande, BANDEH, BANDEV, blanc);
			actualiser();
		}

		
		while(clic.x <=29 && (clic.y >=30 && clic.y<= 59))
		{	
			afficher_image("images/rectangle_vide_allumer.bmp", rect_vide);
			afficher_texte("? Selectionner 2 points pour tracer un rectangle vide.", 13, bande, noir);
			actualiser();
			rectangle_vide(p1, p2, &clic, Couleur_def);	
			dessiner_rectangle(bande, BANDEH, BANDEV, blanc);//rectangle_vide
			actualiser();
		}
		
		while(clic.x <=29 && (clic.y >=60 && clic.y<= 89))
		{	
			afficher_image("images/rectangle_plein_allumer.bmp", rect_plein);
			afficher_texte("? Selectionner 2 points pour tracer un rectangle plein.", 13, bande, noir);
			actualiser();
			rectangle_plein(p1, p2, &clic, Couleur_def);
			dessiner_rectangle(bande, BANDEH, BANDEV, blanc);	//rectangle plein
			actualiser();
		}


		while(clic.x <=29 && (clic.y >=90 && clic.y<= 119))
		{	
			afficher_image("images/cercle_vide_allumer.bmp", cerc_vide);
			afficher_texte("? Selectionner 2 points pour tracer un cercle vide.", 13, bande, noir);
			actualiser();
			cercle_vide(p1, p2, &clic, Couleur_def);
			dessiner_rectangle(bande, BANDEH, BANDEV, blanc);	//cercle_vide
			actualiser();
		}


		while(clic.x <=29 && (clic.y >=120 && clic.y<= 149))
		{	
			afficher_image("images/disque_allumer.bmp", disq);
			afficher_texte("? Selectionner 2 points pour tracer un cercle plein.", 13, bande, noir);
			actualiser();
			disque(p1, p2, &clic, Couleur_def);
			dessiner_rectangle(bande, BANDEH, BANDEV, blanc);	//disque
			actualiser();
		}


		while(clic.x <=29 && (clic.y >=150 && clic.y<= 179))
		{
			afficher_image("images/polygone_allumer.bmp", poly);
			afficher_texte("? Selectionner des points pour tracer un polygone et ensuite faites un clic droit pour fermer le polygone.", 13, bande, noir);
			actualiser();
			polygone_vide(&clic, Couleur_def);
			dessiner_rectangle(bande, BANDEH, BANDEV, blanc);	//polygone 
			actualiser();
		}

		while(clic.x <=29 && (clic.y >=180 && clic.y<= 209))
		{	
			afficher_image("images/polygone_plein_allumer.bmp", poly_plein);
			afficher_texte("? Selectionner des points pour tracer un polygone et ensuite faites un clic droit pour fermer le polygone.", 13, bande, noir);
			actualiser();
			polygone_plein(&clic, Couleur_def);
			dessiner_rectangle(bande, BANDEH, BANDEV, blanc);	//polygone plein
			actualiser();
		}

		if(clic.x <=29 && (clic.y >=210 && clic.y<= 239))
		{	
			afficher_image("images/texte_allumer.bmp", txt);
			afficher_texte("? Selectionner un point pour ecrire puis choisissez la taille de votre texte.", 13, bande, noir);
			actualiser();
			inserer_texte(&clic, Couleur_def);
			dessiner_rectangle(bande, BANDEH, BANDEV, blanc); //Inserer texte
			actualiser();
		}
	
		if(clic.x <=29 && (clic.y >=240 && clic.y<= 269))
		{
			afficher_image("images/crayon_allumer.bmp", cray);
			afficher_texte("? Faites un clic gauche pour commencer a dessiner et un autre pour arreter.", 13, bande, noir);
			actualiser();

		
			while(clic.x <=29 && (clic.y >=240 && clic.y<= 269))
			{	
				crayon(&clic, Couleur_def);//Crayon
				actualiser();
			}
		}

		if(clic.x <=29 && (clic.y >=270 && clic.y<= 299))
		{
			afficher_texte("? Faites un clic gauche pour commencer a effacer et un autre pour arreter.", 13, bande, noir);
			afficher_image("images/gomme_allumer.bmp", gom);
			actualiser();

			while(clic.x <=29 && (clic.y >=270 && clic.y<= 299))
			{	
				gomme(&clic);
				actualiser(); //gomme
			}

		}

		if(clic.x <=29 && (clic.y >=300 && clic.y<= 329))
		{	
			Point rect_gris={29,300};
			Point rect_gris2={0,329};
			afficher_image("images/choix_couleur2.bmp", color);
			afficher_texte("? Choisissez une couleur.", 13, bande, noir);
			actualiser(); 

			Couleur_def = choix_couleur(&clic);
		
			dessiner_rectangle(rect_gris,70, 90, gris);
			dessiner_rectangle(rect_gris2, 40, 90, gris);
			dessiner_rectangle(bande, BANDEH, BANDEV, blanc);
			actualiser();

			
			//printf("on a passer couleur\n");

			 //Choix Couleur
		}

		/*if(clic.x <=29 && (clic.y >=300 && clic.y<= 329))
		{
			clearAll(&clic);
		}*/
			
		if((clic.x >=35 && clic.x <=60) && (clic.y >=0 && clic.y<= 25))
		{
			dessiner_rectangle(page_outils, OUTILH, OUTILV, blanc);
			actualiser();
			sauvegarder(SDL_GetVideoSurface());
		}
	}
    // fin de la session graphique
    fermer_fenetre();
    return 0;
}


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
		
		rayonX = (rayon.x - centre.x) * (rayon.x - centre.x);
		rayonY = (rayon.y - centre.y) * (rayon.y - centre.y);
		rayonFinal = sqrt(rayonX + rayonY);
		
	
	
	if(centre.x >= OUTILH)
	{	
		dessiner_cercle(centre, rayonFinal, couleur);
	}
	
}


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

		rayonX = (rayon.x - centre.x) * (rayon.x - centre.x);
		rayonY = (rayon.y - centre.y) * (rayon.y - centre.y);
		rayonFinal = sqrt(rayonX + rayonY);
	
	if(centre.x >= OUTILH)
	{	
		dessiner_disque(centre, rayonFinal, couleur);
	}	
	
}


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

void inserer_texte(Point *clic, int couleur)
	{
		Point txt={0,210};
		
		char texte[100];
		int tailleTexte = 0;
		Point ouCa = attendre_clic();

		
		if(ouCa.x >= OUTILH)
		{		
			printf("Entrez votre texte :\n");
			scanf("%s", texte);

			printf("Entrez la taille de votre texte :\n");
			scanf("%d", &tailleTexte);

			afficher_texte(texte, tailleTexte, ouCa, couleur);
		}
		else
		{
			*clic = ouCa;
			afficher_image("images/texte.bmp", txt);
			
		}

	}

void crayon(Point *clic, int couleur)
	{
		Point cray={0,240};

		Point centre={0,0};
		Point rayon={1,0};
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

				printf("clic_gauche.x = %d et clic_gauche.y = %d\n",clic_gauche.x,clic_gauche.y);
				if(clic_gauche.x <= OUTILH )
				{
					*clic = clic_gauche;
					afficher_image("images/crayon.bmp", cray);	
					break;
				}
				centre=deplacement_souris_a_eu_lieu();
				//printf("centre.x = %d et centre.y = %d\n",centre.x,centre.y);

				if(centre.x >= OUTILH)
				{	
					dessiner_disque(centre, rayon.x, couleur);
					actualiser();
					dessiner_ligne(centre,clic_avant, couleur);	

				}	
				clic_avant=centre;

				
				traiter_evenements();
				clic_gauche2 = clic_a_eu_lieu();

				//printf("clicGau2.x = %d et clicGau2.y = %d\n",clic_gauche2.x,clic_gauche2.y);

				if(clic_gauche2.x != -1 && clic_gauche2.y != -1)
				{	
					clic_gauche.x = 30;
					clic_gauche.y = -1;
				}
					
				//	printf("clic.x = %d et clic.y = %d\n",centre.x,centre.y); 
				reinitialiser_evenements();
				
			}		
				
		
		if(clic_gauche2.x <= OUTILH )
		{
			*clic = clic_gauche2;
			afficher_image("images/crayon.bmp", cray);	
		}
		
		

	}

void gomme(Point *clic)
	{
		Point gom={0,270};
		Point centre={0,0};
		Point rayon={5,0};
		Point clic_gauche={0,0};	
		Point clic_gauche2={101,0};
		
		Point bande={100,575};

		traiter_evenements();
			
		clic_gauche = clic_a_eu_lieu();
		printf("clic.x = %d et clic.y = %d\n",clic_gauche.x,clic_gauche.y);

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
					dessiner_disque(centre, rayon.x, blanc);
					actualiser();
				}	

				traiter_evenements();

				clic_gauche2 = clic_a_eu_lieu();

				printf("clicGau2.x = %d et clicGau2.y = %d\n",clic_gauche2.x,clic_gauche2.y);

				if(clic_gauche2.x != -1 && clic_gauche2.y != -1)
				{	
					clic_gauche.x = 30;
					clic_gauche.y = -1;

				}
					
			//	printf("clic.x = %d et clic.y = %d\n",centre.x,centre.y); 
				reinitialiser_evenements();
			}		
				
		if(clic_gauche2.x <= OUTILH )
		{
			*clic = clic_gauche2;
			afficher_image("images/gomme.bmp", gom);	
		}

	}

int choix_couleur(Point *clic)
	{
		int R = 0, G = 0, B = 0;

		Point color={0,300};
		Point choix_clic={0,0};
		Point rect_gris={29,300};
		Point rect_gris2={0,329};
		//Point color2={0,330};
		//Point palette={0,500};
		//Point test={0,304};
		
		choix_clic = attendre_clic();
		printf("choix_clic.x = %d, choix_clic.y = %d\n", choix_clic.x, choix_clic.y);
		/*dessiner_rectangle(color, 96, 74, gris);
			actualiser();
			afficher_image("images/couleurs/noir.bmp", color);
			actualiser();
*/
			/*dessiner_rectangle(test, 20, 20, bleu);
			actualiser();*/
		if((choix_clic.x >= 5 && choix_clic.x <= 25) && (choix_clic.y >=304 && choix_clic.y<= 324))
		{
			//printf("t rentrer\n");
			afficher_image("images/couleurs/noir.bmp", color);
			actualiser();
			*clic = rect_gris;
			dessiner_rectangle(rect_gris,70, 90, gris);
			dessiner_rectangle(rect_gris2, 40, 90, gris);
			actualiser();
			return noir;
		}
		if((choix_clic.x >= 27 && choix_clic.x <= 47) && (choix_clic.y >=304 && choix_clic.y<= 324))
		{
			//dessiner_rectangle(color, 96, 74, gris);
			//actualiser();
			afficher_image("images/couleurs/gris.bmp", color);
			actualiser();
			*clic = choix_clic;
			return gris;
		}
		else if((choix_clic.x >= 49 && choix_clic.x <= 69) && (choix_clic.y >=304 && choix_clic.y<= 324))
		{
			afficher_image("images/couleurs/blanc.bmp", color);
			actualiser();
			*clic = choix_clic;
			return blanc;
		}
		else if((choix_clic.x >= 71 && choix_clic.x <= 91) && (choix_clic.y >=304 && choix_clic.y<= 324))
		{
			//dessiner_rectangle(color, 96, 74, gris);
			//actualiser();
			afficher_image("images/couleurs/rouge.bmp", color);
			actualiser();
			*clic = choix_clic;
			return rouge;
		}
		else if((choix_clic.x >= 5 && choix_clic.x <= 25) && (choix_clic.y >=328 && choix_clic.y<= 348))
		{
			printf("t rentrer\n");
			afficher_image("images/couleurs/orange.bmp", color);
			actualiser();
			*clic = rect_gris;
			return orange;
		}
		else if((choix_clic.x >= 27 && choix_clic.x <= 47) && (choix_clic.y >=328 && choix_clic.y<= 348))
		{
			afficher_image("images/couleurs/jaune.bmp", color);
			actualiser();
			*clic = choix_clic;
			return jaune;
		}
		else if((choix_clic.x >= 49 && choix_clic.x <= 69) && (choix_clic.y >=328 && choix_clic.y<= 348))
		{
			afficher_image("images/couleurs/vert.bmp", color);
			actualiser();
			*clic = choix_clic;
			return vert;
		}
		else if((choix_clic.x >= 71 && choix_clic.x <= 91) && (choix_clic.y >=328 && choix_clic.y<= 348))
		{
			afficher_image("images/couleurs/bleu.bmp", color);
			actualiser();
			*clic = choix_clic;
			return bleu;
		}
		else if((choix_clic.x >= 5 && choix_clic.x <= 25) && (choix_clic.y >=352 && choix_clic.y<= 412))
		{
			printf("t rentrer\n");
			afficher_image("images/couleurs/violet.bmp", color);
			actualiser();
			*clic = rect_gris;
			return violet;
		}
		else if((choix_clic.x >= 27 && choix_clic.x <= 47) && (choix_clic.y >=352 && choix_clic.y<= 412))
		{
			afficher_image("images/couleurs/rose.bmp", color);
			actualiser();
			*clic = choix_clic;
			return magenta;
		}
		else if((choix_clic.x >= 49 && choix_clic.x <= 69) && (choix_clic.y >=352 && choix_clic.y<= 412))
		{
			afficher_image("images/couleurs/marron.bmp", color);
			actualiser();
			*clic = choix_clic;
			return marron;
		}
		else if((choix_clic.x >= 71 && choix_clic.x <= 91) && (choix_clic.y >=352 && choix_clic.y<= 412))
		{
			afficher_image("images/couleur.bmp", color);
			dessiner_rectangle(rect_gris,70, 90, gris);
			dessiner_rectangle(rect_gris2, 40, 90, gris);
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
			afficher_image("images/couleur.bmp", color);
			dessiner_rectangle(rect_gris,70, 90, gris);
			dessiner_rectangle(rect_gris2, 40, 90, gris);

			actualiser();
		}
		
		*clic = attendre_clic();
			//afficher_image("images/texte.bmp", txt);	

		return noir;

	}

char charger(char chemin_fichier[])
	{

		printf("Entrez le chemin ou se trouve le fichier :\n");
		scanf("%s", chemin_fichier);
		
			
		return chemin_fichier[200];
	}
void sauvegarder( SDL_Surface *source)
	{
		printf("Le fichier a ete sauvegarder !\n");
		SDL_SaveBMP(source,"Cpaint.bmp");
	}


/*void clearAll(Point *clic)
	{

		dessiner_rectangle(page_blanche, RESH, RESV, blanc);
		actualiser();

	}
*/



























