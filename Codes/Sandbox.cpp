/*
DOCUMENT CODE "Sandbox.cpp"
CREATION DATE 2017-05-18
SIGNATURE CODE_SANDBOX
TOPIC 沙箱 用来写一些没用的测试性东西
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_SANDBOX

//                                                     /*[*/#include<stdio.h>//
//                         #include<stdlib.h>//]++++[->++[->+>++++<<]<][(c)2013]
//                        #ifndef                                           e//[o
//                       #include<string.h>//]![misaka.c,size=3808,crc=d0ec3b36][
//                      #define e                                           0x1//
//                     typedef struct{int d,b,o,P;char*q,*p;}f;int p,q,d,b,_=0//|
//                  #include __FILE__//]>>>[->+>++<<]<[-<<+>>>++<]>>+MISAKA*IMOUTO
//                #undef e//[->[-<<+<+<+>>>>]<<<<<++[->>+>>>+<<<<<]>+>+++>+++[>]]b
//             #define e(c)/**/if((_!=__LINE__?(_=__LINE__):0)){c;}//[20002,+[-.+]
//            ,O,i=0,Q=sizeof(f);static f*P;static FILE*t;static const char*o[]={//
//          "\n\40\"8oCan\40not\40open %s\n\0aaFbfeccdeaEbgecbbcda6bcedd#e(bbed$bbd",
//        "a6bgcdbbccd#ead$c%bcdea7bccde*b$eebbdda9bsdbeccdbbecdcbbcceed#eaa&bae$cbe",
//       "e&cbdd$eldbdeedbbdede)bdcdea&bbde1bedbbcc&b#ccdee&bdcdea'bbcd)e'bad(bae&bccd",
//      "e&bbda1bdcdee$bbce#b$c&bdedcd%ecdca4bhcdeebbcd#e$b#ecdcc$bccda7bbcc#e#d%c*bbda",
//     ">bad/bbda"};static int S(){return(o[p][q]);}static/**/int/**/Z=0  ;void/**/z(int//
//    l){if(/**/Z-l){Z=l;q++;if(p<b*5&&!S()){p+=b;q=0;}}}int main(int I,    /**/char**l){//
//   d=sizeof(f*);if(1<(O=_)){b=((sizeof(o)/sizeof(char*))-1)/4;q=22; p=     0;while(p<b*5){
//  /*<*/if(Z-1){d=S()>96;i=S()-(d?96:32) ;q++;if(p<b*5&&!S()){p+=b;  q=      0;}Z=1;}/*[[*/
//  while(i){_=o[0][S()-97];I=_-10?b:1;   for( ;I--;)putchar(_ );if   (!      --i||d)z(~i );}
// if(p==b*5&&O){p-=b;O--;}}return 0U;   }if(! (P=( f*)calloc /*]*/  (Q        ,I)))return 1;
// {;}for(_=p=1;p<I;p++){e(q=1);while    (q<   p&&  strcmp(  l[p     ]         ,l[(q)]))++  q;
// t=stdin;if(q<p){(void)memcpy/* "      */    (&P  [p],&P   [q     ]          ,Q);continue ;}
//if(strcmp(l[p],"-")){t=fopen(l         [     p]   ,"rb"   )                  ;if(!t ){{;}  ;
//printf(05+*o,l[p ]);return+1;                      {;}                       }}_=b= 1<<16   ;
//*&O=5;do{if(!(P[p].q=realloc   (P[p].q,(P[p].P     +=       b)+1))){return   01;}O   &=72   /
//6/*][*/;P[p].o+=d=fread(P[p]      .q       +P[     p           ].       o,  1,b,t)   ;}//
// while(d==b)      ;P [p].q[       P[       p]                  .o       ]=  012;d    =0;
// e(fclose(t        )  );P         [p]      .p                  =P[      p]  .q;if    (O)
// {for(;d<P[            p]          .o     ;d=                   q+     1)    {q=     d;
//  while(q<P[                        p].o&&P[                    p].q[q]-     10     ){
//  q++;}b=q-d;                         _=P                         [p].        d     ;
//  if(b>_){/*]b                                                                */
//   P[p].d=b;}{;                                                                }
//   #undef/*pqdz'.*/  e//                                                      ;
//   #define/*s8qdb]*/e/**/0                                                   //
//   //<<.<<.----.>.<<.>++.++<                                              .[>]
//   /*P[*/P[p].b++;continue;}}}t=                                       stdout;
//  for (p=1;p<I;p++){/**/if(P[p].b>i                               ){i=P[p].b;}}
// if  (O){for(p=0;p<i;p++){q=0;/*[*/while(I               >++q){_=P[q].p-P[q ].q;
//b=   0;if(_<P[q ].o){while(012-*P[q].p)     {putchar(*(P[q].p++));b++;}P[q]. p++;
//}   ;while (P[  q].d>b++)putchar(040);}             putchar(10);}return 0;}p   =1;
//   for(;   p<I   ;p++)fwrite(P[p] .q,P[              p].o,1,t);return 0 ;}//
//  #/*]     ]<.    [-]<[-]<[- ]<[    -]<               [-  ]<;*/elif  e    //b
// |(1        <<     ( __LINE__        /*               >>   `*//45))  |     01U
//             #                       /*               */     endif            //

#include <cstdlib>
#include <iostream>
#include <Windows.h>
#include <SFML/Graphics.hpp>
#include "ImGui/imgui-setup.h"
using namespace std;
using namespace sf;

RenderWindow win;

const String operator""S(const char* c, std::size_t l) { return String::fromUtf8(c, c + l); }
String u8ToSfString(const char* u8string) { return String::fromUtf8(u8string, u8string + strlen(u8string)); }
String u8ToSfString(const string& str) { return String::fromUtf8(str.begin(), str.end()); }
wchar_t convertBufferWStr[32 * 1024];
char convertBufferStr[32 * 1024];
const UINT codepage = 54936; // GB18030-2005 for Vista+ versions of Windows
void convert936ToUtf8(string& str) {
	convertBufferWStr[MultiByteToWideChar(codepage, 0, str.c_str(), str.size(), convertBufferWStr, 32 * 1024)] = '\0';
	auto u8result = sf::String(convertBufferWStr).toUtf8();
	str.clear();
	str.reserve(u8result.size());
	for (auto i : u8result)
		str.push_back((char)i);
}
void convertUtf8To936(string& str) {
	wstring wstr = String::fromUtf8(str.begin(), str.end()).toWideString();
	convertBufferStr[WideCharToMultiByte(codepage, 0, wstr.c_str(), wstr.size(), convertBufferStr, 32 * 1024, NULL, NULL)] = '\0';
	str = string(convertBufferStr);
}

template<typename Type>
VertexArray renderRect(Rect<Type> rect, Color color = Color::Black) {
	VertexArray arr;
	arr.append(Vertex(Vector2f(rect.left, rect.top), color));
	arr.append(Vertex(Vector2f(rect.left + rect.width, rect.top), color));
	arr.append(Vertex(Vector2f(rect.left + rect.width, rect.top + rect.height), color));
	arr.append(Vertex(Vector2f(rect.left, rect.top + rect.height), color));
	arr.append(Vertex(Vector2f(rect.left, rect.top), color));
	arr.setPrimitiveType(PrimitiveType::LinesStrip);
	return arr;
}

int main(int argc, char* argv[]) {

	// the C locale will be UTF-8 enabled English;
// decimal dot will be German
// date and time formatting will be Japanese
	//setlocale(LC_ALL, "en_US.UTF-8");
	//setlocale(LC_NUMERIC, "de_DE.UTF-8");
	//setlocale(LC_TIME, "ja_JP.UTF-8");
	setlocale(LC_ALL, "ja_JP.UTF-8");

	wchar_t str[100];
	time_t t = std::time(NULL);
	wcsftime(str, 100, L"%A %c", localtime(&t));
	wprintf(L"Number: %.2f\nDate: %Ls\n", 3.14, str);

	//int prime[10001] = {};

	//for (int i = 2; i <= 10000; i++) {
	//	if (prime[i] == 0)
	//		for (int j = i + i; j <= 10000; j += i)
	//			prime[j] = i;
	//}

	//int a;
	//cin >> a;
	//if (prime[a] == 0)
	//	cout << "true" << endl;
	//else
	//	cout << "false " << prime[a] << endl;

	//for (int i = 2; i <= 10000; i++)
	//	if (prime[i])
	//		cout << i << ',';

	Font f;
	f.loadFromFile("C:/Windows/Fonts/simsun.ttc");
	Text t12, t14, t16, t18, t48;
	t12.setFont(f);
	t12.setCharacterSize(12);
	t12.setString(u8"宋体（12像素高）"S);
	t12.setFillColor(Color::Black);

	t14.setFont(f);
	t14.setCharacterSize(14);
	t14.setString(L"宋体（14像素高）");
	t14.setFillColor(Color::Black);
	t14.move(0, t12.getLocalBounds().height);

	t16.setFont(f);
	t16.setCharacterSize(16);
	t16.setString(L"宋体（16像素高）");
	t16.setFillColor(Color::Black);
	t16.move(0, t12.getLocalBounds().height + t14.getLocalBounds().height);

	t18.setFont(f);
	t18.setCharacterSize(18);
	t18.setString(L"宋体（18像素高）");
	t18.setFillColor(Color::Black);
	t18.move(0, t12.getLocalBounds().height + t14.getLocalBounds().height + t16.getLocalBounds().height);

	t48.setFont(f);
	t48.setCharacterSize(48);
	t48.setString(L"宋体（48像素高）");
	t48.setFillColor(Color::Black);
	//t48.setOutlineThickness(4.0f);
	//t48.setOutlineColor(Color::Black);
	t48.move(0, t12.getLocalBounds().height + t14.getLocalBounds().height + t16.getLocalBounds().height + t18.getLocalBounds().height);



	win.create(VideoMode(1080, 608), "ImGui Snippet");
	win.setVerticalSyncEnabled(true);
	win.resetGLStates();

	imgui::SFML::Init(win, true);

	Clock deltaClock;
	while (win.isOpen()) {
		Event e;
		while (win.pollEvent(e)) {
			imgui::SFML::ProcessEvent(e);
			if (e.type == Event::Closed)
				win.close();
			else if (e.type == Event::Resized)
				win.setView(View(FloatRect(0, 0, e.size.width, e.size.height)));
		}

		imgui::SFML::Update(win, deltaClock.restart());

		imgui::ShowDemoWindow();
		imgui::ShowMetricsWindow();

		win.clear(Color(192, 192, 192));
		imgui::SFML::Render(win);
		win.draw(t12);
		win.draw(t14);
		win.draw(t16);
		win.draw(t18);
		win.draw(t48);
		win.draw(renderRect(t12.getGlobalBounds()));
		win.draw(renderRect(t14.getGlobalBounds()));
		win.draw(renderRect(t16.getGlobalBounds()));
		win.draw(renderRect(t18.getGlobalBounds()));
		win.draw(renderRect(t48.getGlobalBounds()));
		win.display();
	}

	return 0;
}


#endif
