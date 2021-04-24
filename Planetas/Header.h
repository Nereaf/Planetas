#define CR 0.0175
#define MYTIEMPO 41
#define PI 3.141592
#define T 2

typedef struct {
	float distancia;
	float velocidad_Trans;
	float angulo_Tran;
	float velocidad_Rot;
	float angulo_Rot;
	float tamano;
	int lista;
	float cR;
	float cG;
	float cB;
	BOOLEAN tOrbita;
	BOOLEAN hijos;
	int textura;
} Planeta;


void myCamera();
void myTeclado(unsigned char tras, int x, int y);
void myTeclasespeciales(int cursor, int x, int y);
void myOrbitas(int radio);
void CreaListaOrbita(void);
void myEjes();
//función de telescopio para la luna e iss
void myTelescopioSatelite(float distancia, float angulo, float distancia_sat, float angulo_sat);
void myTelescopio(float distancia, float angulo, float distancia_obj, float angulo_obj);
void myMenu(void);
void onMenu(int option);

