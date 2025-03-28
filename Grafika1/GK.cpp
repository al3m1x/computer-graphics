/******************************************************************
 Grafika komputerowa, œrodowisko MS Windows - program  przyk³adowy
 *****************************************************************/

#include <windows.h>
#include <gdiplus.h>
using namespace Gdiplus;


//deklaracja funkcji obslugi okna
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//funkcja Main - dla Windows
 int WINAPI WinMain(HINSTANCE hInstance,
               HINSTANCE hPrevInstance,
               LPSTR     lpCmdLine,
               int       nCmdShow)
{
	MSG meldunek;		  //innymi slowy "komunikat"
	WNDCLASS nasza_klasa; //klasa g³ównego okna aplikacji
	HWND okno;
	static char nazwa_klasy[] = "Podstawowa";
	
	GdiplusStartupInput gdiplusParametry;// parametry GDI+; domyœlny konstruktor wype³nia strukturê odpowiednimi wartoœciami
	ULONG_PTR	gdiplusToken;			// tzw. token GDI+; wartoœæ uzyskiwana przy inicjowaniu i przekazywana do funkcji GdiplusShutdown
   
	// Inicjujemy GDI+.
	GdiplusStartup(&gdiplusToken, &gdiplusParametry, NULL);

	//Definiujemy klase g³ównego okna aplikacji
	//Okreslamy tu wlasciwosci okna, szczegoly wygladu oraz
	//adres funkcji przetwarzajacej komunikaty
	nasza_klasa.style         = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	nasza_klasa.lpfnWndProc   = WndProc; //adres funkcji realizuj¹cej przetwarzanie meldunków 
 	nasza_klasa.cbClsExtra    = 0 ;
	nasza_klasa.cbWndExtra    = 0 ;
	nasza_klasa.hInstance     = hInstance; //identyfikator procesu przekazany przez MS Windows podczas uruchamiania programu
	nasza_klasa.hIcon         = 0;
	nasza_klasa.hCursor       = LoadCursor(0, IDC_ARROW);
	nasza_klasa.hbrBackground = (HBRUSH) GetStockObject(GRAY_BRUSH);
	nasza_klasa.lpszMenuName  = "Menu" ;
	nasza_klasa.lpszClassName = nazwa_klasy;

    //teraz rejestrujemy klasê okna g³ównego
    RegisterClass (&nasza_klasa);
	
	/*tworzymy okno g³ówne
	okno bêdzie mia³o zmienne rozmiary, listwê z tytu³em, menu systemowym
	i przyciskami do zwijania do ikony i rozwijania na ca³y ekran, po utworzeniu
	bêdzie widoczne na ekranie */
 	okno = CreateWindow(nazwa_klasy, "Grafika komputerowa", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
						CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
	
	
	/* wybór rozmiaru i usytuowania okna pozostawiamy systemowi MS Windows */
   	ShowWindow (okno, nCmdShow) ;
    
	//odswiezamy zawartosc okna
	UpdateWindow (okno) ;

	// G£ÓWNA PÊTLA PROGRAMU
	while (GetMessage(&meldunek, NULL, 0, 0))
     /* pobranie komunikatu z kolejki; funkcja GetMessage zwraca FALSE tylko dla
	 komunikatu WM_QUIT; dla wszystkich pozosta³ych komunikatów zwraca wartoœæ TRUE */
	{
		TranslateMessage(&meldunek); // wstêpna obróbka komunikatu
		DispatchMessage(&meldunek);  // przekazanie komunikatu w³aœciwemu adresatowi (czyli funkcji obslugujacej odpowiednie okno)
	}

	GdiplusShutdown(gdiplusToken);
	
	return (int)meldunek.wParam;
}

/********************************************************************
FUNKCJA OKNA realizujaca przetwarzanie meldunków kierowanych do okna aplikacji*/
LRESULT CALLBACK WndProc (HWND okno, UINT kod_meldunku, WPARAM wParam, LPARAM lParam)
{
	HMENU mPlik, mInfo, mGlowne;
    	
/* PONI¯SZA INSTRUKCJA DEFINIUJE REAKCJE APLIKACJI NA POSZCZEGÓLNE MELDUNKI */
	switch (kod_meldunku) 
	{
	case WM_CREATE:  //meldunek wysy³any w momencie tworzenia okna
		mPlik = CreateMenu();
		AppendMenu(mPlik, MF_STRING, 100, "&Zapiszcz...");
		AppendMenu(mPlik, MF_SEPARATOR, 0, "");
		AppendMenu(mPlik, MF_STRING, 101, "&Koniec");
		mInfo = CreateMenu();
		AppendMenu(mInfo, MF_STRING, 200, "&Autor...");
		mGlowne = CreateMenu();
		AppendMenu(mGlowne, MF_POPUP, (UINT_PTR) mPlik, "&Plik");
		AppendMenu(mGlowne, MF_POPUP, (UINT_PTR) mInfo, "&Informacja");
		SetMenu(okno, mGlowne);
		DrawMenuBar(okno);

	case WM_COMMAND: //reakcje na wybór opcji z menu
		switch (wParam)
		{
		case 100: if(MessageBox(okno, "Zapiszczeæ?", "Pisk", MB_YESNO) == IDYES)
					MessageBeep(0);
                  break;
		case 101: DestroyWindow(okno); //wysylamy meldunek WM_DESTROY
        		  break;
		case 200: MessageBox(okno, "Imiê i nazwisko:\nNumer indeksu: ", "Autor", MB_OK);
		}
		return 0;
	
	case WM_LBUTTONDOWN: //reakcja na lewy przycisk myszki
		{
			int x = LOWORD(lParam);
			int y = HIWORD(lParam);

			return 0;
		}

	case WM_PAINT:
		{
			PAINTSTRUCT paint;
			HDC kontekst;

			kontekst = BeginPaint(okno, &paint);
		
			// MIEJSCE NA KOD GDI

			HPEN pioro = CreatePen(PS_SOLID, 5, RGB(30,144,255));
			SelectObject(kontekst, pioro);


			HBRUSH brush = CreateSolidBrush(RGB(30, 144, 255));
			SelectObject(kontekst, brush);

			Ellipse(kontekst, 0, 0, 400, 400);
			ExtFloodFill(kontekst, 200, 200, RGB(30, 144, 255), FLOODFILLBORDER);
			
			DeleteObject(brush);
			DeleteObject(pioro);
			HPEN pioro2 = CreatePen(PS_SOLID, 5, RGB(255, 255, 255));

			HBRUSH brush2 = CreateSolidBrush(RGB(255, 255, 255));
			SelectObject(kontekst, brush2);
			SelectObject(kontekst, pioro2);

			POINT PolygonPoints[4];
			PolygonPoints[0].x = 105;
			PolygonPoints[0].y = 350;
			PolygonPoints[1].x = 105;
			PolygonPoints[1].y = 220;
			PolygonPoints[2].x = 165;
			PolygonPoints[2].y = 220;
			PolygonPoints[3].x = 165;
			PolygonPoints[3].y = 350;

			Polygon(kontekst, PolygonPoints, 4);

			POINT BeizerPoints[4];
			BeizerPoints[0].x = 165;
			BeizerPoints[0].y = 220;
			BeizerPoints[1].x = 185;
			BeizerPoints[1].y = 180;
			BeizerPoints[2].x = 200;
			BeizerPoints[2].y = 180;
			BeizerPoints[3].x = 230;
			BeizerPoints[3].y = 180;


			PolyBezier(kontekst, BeizerPoints, 4);

			POINT BeizerPoints2[4];
			BeizerPoints2[0].x = 105;
			BeizerPoints2[0].y = 220;
			BeizerPoints2[1].x = 135;
			BeizerPoints2[1].y = 110;
			BeizerPoints2[2].x = 200;
			BeizerPoints2[2].y = 120;
			BeizerPoints2[3].x = 230;
			BeizerPoints2[3].y = 120;


			PolyBezier(kontekst, BeizerPoints2, 4);

			SelectObject(kontekst, brush2);
			POINT PolygonPoints2[3];
			PolygonPoints2[0].x = 230;
			PolygonPoints2[0].y = 80;
			PolygonPoints2[1].x = 230;
			PolygonPoints2[1].y = 220;
			PolygonPoints2[2].x = 330;
			PolygonPoints2[2].y = 150;

			Polygon(kontekst, PolygonPoints2, 3);

			ExtFloodFill(kontekst, 130, 230, RGB(255, 255, 255), FLOODFILLBORDER);

			DeleteObject(brush2);
			DeleteObject(pioro2);
			// utworzenie obiektu umo¿liwiaj¹cego rysowanie przy u¿yciu GDI+
			// (od tego momentu nie mo¿na u¿ywaæ funkcji GDI
			Graphics grafika(kontekst);
			
			// MIEJSCE NA KOD GDI+


			// utworzenie czcionki i wypisanie tekstu na ekranie
			FontFamily  fontFamily(L"Times New Roman");
			Font        font(&fontFamily, 24, FontStyleRegular, UnitPixel);
			PointF      pointF(100.0f, 400.0f);
			SolidBrush  solidBrush(Color(255, 0, 0, 255));


			EndPaint(okno, &paint);

			return 0;
		}
  	
	case WM_DESTROY: //obowi¹zkowa obs³uga meldunku o zamkniêciu okna
		PostQuitMessage (0) ;
		return 0;
    
	default: //standardowa obs³uga pozosta³ych meldunków
		return DefWindowProc(okno, kod_meldunku, wParam, lParam);
	}
}
