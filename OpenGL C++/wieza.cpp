#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

GLfloat rotObsY     = 40.0;
GLfloat rotObsX     = 40.0;
GLfloat rotObsZ     = 0.0;
GLfloat rotPodstawy = 0.0;
GLfloat rotRamienia1= 40.0;
GLfloat rotRamienia2= -40.0;
GLfloat rotGlowicy  = 20.0;
GLfloat rozUchwytow = 0.5;
 
GLfloat rotacjaPlanety = 0.0;
GLfloat rotacjaKsiezyca = 0.0;
GLfloat spinPlanety = 0.0;
 
GLfloat odlMin = -190;
GLfloat Odl = -180;
GLfloat odlMax = -10;
GLfloat zoomSpeed = 0.5;
GLUquadricObj* orbitaPlanety;
GLUquadricObj* orbitaKsiezyca;
GLUquadricObj* cylinder;
GLUquadricObj* dysk;
GLUquadricObj* orbita;
GLUquadricObj* glownaOrbita;
GLUquadricObj* orbitaKsiezyc;
 
 
float alp=0, spin=0,moon=0;
//////////////////////////////////////////////////////////////////////////////////////////
// Funkcja inicjujaca elementy skladowe ramienia robota zamodelowane jako kwadryki
//
void InicjujKwadryki(void)
{

}
 
GLfloat zmienna = 0;

int i=0;
GLfloat obrot=0;
GLfloat poruszaj = 0;
GLfloat poruszajKsiezyc = 0;
int przesunWiatrak=0;

//////////////////////////////////////////////////////////////////////////////////////////
// Funkcja rysujaca obraz sceny widzianej z biezacej pozycji obserwatora
// Zalozenie: Funkcja glutWireSpehere moze ryswac tylko sfere o promieniu 1  
void RysujWieza()
{
  // Pocztaek tworzenia ukladu wspolrzednych
  glBegin(GL_LINES);
 
  // Os X Red
  glColor3f(1.0, 0.0, 0.0);
  glVertex3f(-40.0, 0.0, 0.0);
  glVertex3f(40.0, 0.0, 0.0);
 
  // Os Y Green
  glColor3f(0.0,1.0,0.0);
  glVertex3f(0.0, -40.0, 0.0);
  glVertex3f(0.0, 20.0, 0.0);
 
  // Os Z Blue
  glColor3f(0.0,0.0,1.0);
  glVertex3f(0.0, 0.0, -20.0);
  glVertex3f(0.0, 0.0, 20.0);
 
  // Koniec tworzenia ukladu wspolrzednych
  glEnd();
 


 // Wieża
 
 glTranslatef(80,0,0);
 
  glColor3f(1, 0, 0);
  glPushMatrix();
 
      glTranslatef(0, 5, 0);
      glRotatef(45.0, 0, 1, 0);
      glScalef(4.23,10,4.23);  
      glutSolidCube(1);
  glPopMatrix();
 
  glColor3f(0, 1, 0);
  glPushMatrix();
      glTranslatef(0,11.5,0);
      glScalef(8, 3, 8);
      glutSolidCube(1);
  glPopMatrix();
 
  //1
  glColor3f(0,0,1);
  glPushMatrix();
    glTranslatef(3,13.5,3);
    glutSolidCube(2);
  glPopMatrix();
  //2
  glPushMatrix();
      glTranslatef(-3, 13.5, 3);
      glutSolidCube(2);
  glPopMatrix();
  //3
  glPushMatrix();
      glTranslatef(-3, 13.5, -3);
      glutSolidCube(2);
  glPopMatrix();
  //4
  glPushMatrix();
      glTranslatef(3, 13.5, -3);
      glutSolidCube(2);
  glPopMatrix();

}
 
//////////////////////////////////////////////////////////////////////////////////////////
// Funkcja generujaca pojedyncza klatke animacji
void WyswietlObraz(void)
{
  // Wyczyszczenie bufora ramki i bufora glebokosci
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
 
  // Powielenie macierzy na wierzcholku stosu
  glPushMatrix();
 
  // Wyznaczenie polozenia obserwatora (przeksztalcenie uladu wspolrzednych
  // sceny do ukladu wspolrzednych obserwatora).
  glTranslatef(0, 0, Odl);
  glRotatef(rotObsX, 1, 0, 0);
  glRotatef(rotObsY,0,1,0);
  glRotatef(rotObsZ, 0, 0, 1);
 
 
  // Generacja obrazu sceny w niewidocznym buforze ramki
  RysujWieza(rotPodstawy, rotRamienia1, rotRamienia2, rotGlowicy, rozUchwytow);
 
  // Usuniecie macierzy lezacej na  wierzcholku stosu (powrot do stanu
  // sprzed wywolania funkcji)
  glPopMatrix();
 
  // Przelaczenie buforow ramki
  glutSwapBuffers();
 
 
}
 
//////////////////////////////////////////////////////////////////////////////////////////
// Funkcja ustawiajaca parametry rzutu perspektywicznego i rozmiary viewportu
void UstawParametryWidoku(int szerokosc, int wysokosc)
{
  // Ustawienie parametrow viewportu
  glViewport(0, 0, szerokosc, wysokosc);
 
  // Przejscie w tryb modyfikacji macierzy rzutowania
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(40.0, (float)szerokosc/(float)wysokosc, 1.0, 1000.0);
 
  // Przejscie w tryb modyfikacji macierzy przeksztalcen geometrycznych
  glMatrixMode(GL_MODELVIEW);
 
  // Zmiana macierzy znajdujacej sie na wierzcholku stosu na macierz jednostkowa
  glLoadIdentity();
}
 
//////////////////////////////////////////////////////////////////////////////////////////
// Funkcja klawiszy specjalnych
void ObslugaKlawiszySpecjalnych(int klawisz, int x, int y)
{
  switch(klawisz)
    {
    case GLUT_KEY_UP:
      rotObsX = rotObsX + 1.0;
      break;
 
    case GLUT_KEY_DOWN:
      rotObsX = rotObsX - 1.0;
      break;
 
    case GLUT_KEY_LEFT:
      rotObsY = rotObsY - 1.0;
      break;
 
    case GLUT_KEY_RIGHT:
      rotObsY = rotObsY + 1.0;
      break;
    }
}
//////////////////////////////////////////////////////////////////////////////////////////
// Funkcja obslugi klawiatury
void ObslugaKlawiatury(unsigned char klawisz, int x, int y)
{
 
  switch(klawisz)
    {
   
   //Sterowanie sceną
    case 'v':
        if (Odl > odlMin)
            Odl--;
        break;
 
    case 'c':
        if (Odl < odlMax)
            Odl++;
        break;
 
    case 'z':
        rotObsZ++;
        break;
 
    case 'x':
        rotObsZ--;
        break;
    case 's':
        przesunWiatrak = (przesunWiatrak > -3) ? przesunWiatrak - 1 : przesunWiatrak ;
        break;
 
    case 'd':
        przesunWiatrak = (przesunWiatrak < 3) ? przesunWiatrak + 1 : przesunWiatrak ;
        break;

  }
  if(klawisz == 27)
      exit(0);      
}
 
//////////////////////////////////////////////////////////////////////////////////////////
// Glowna funkcja programu
int  main(int argc, char **argv)
{
  // Zainicjowanie biblioteki GLUT
  glutInit(&argc, argv);
 
  // Ustawienie trybu wyswietlania
  glutInitDisplayMode (GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
 
  // Ustawienie polozenia dolenego lewego rogu okna
  glutInitWindowPosition(100, 100);
 
  // Ustawienie rozmiarow okna
  glutInitWindowSize(400, 400);
 
  // Utworzenie okna
  glutCreateWindow("Wieza");
 
  // Odblokowanie bufora glebokosci
  glEnable(GL_DEPTH_TEST);
 
  // Ustawienie funkcji wykonywanej na danych w buforze glebokosci
  glDepthFunc(GL_LEQUAL);
 
  // Ustawienie wartosci czyszczacej zawartosc bufora glebokosci
  glClearDepth(1000.0);
 
  // Ustawienie koloru czyszczenia bufora ramki
  glClearColor (0.3, 0.3, 0.3, 0.0);
 
  // Zarejestrowanie funkcji (callback) wyswietlajacej
  glutDisplayFunc(WyswietlObraz);
 
  // Zarejestrowanie funkcji (callback) wywolywanej za kazdym razem kiedy
  // zmieniane sa rozmiary okna
  glutReshapeFunc(UstawParametryWidoku);
 
  // Zarejestrowanie funkcji wykonywanej gdy okno nie obsluguje
  // zadnych zadan
  glutIdleFunc(WyswietlObraz);
 
  // Zarejestrowanie funkcji obslugi klawiatury
  glutKeyboardFunc(ObslugaKlawiatury);
 
  // Zarejestrowanie funkcji obslugi klawiszy specjalnych
  glutSpecialFunc(ObslugaKlawiszySpecjalnych);
 
 
  // Zainicjowanie kwadryk tworzacych ramie robota
  InicjujKwadryki();
 
  // Obsluga glownej petli programu (wywolywanie zarejestrowanych callbackow
  // w odpowiedzi na odbierane zdarzenia lub obsluga stanu bezczynnosci)
  glutMainLoop();
 
  return 0;
}