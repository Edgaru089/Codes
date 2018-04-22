/*
DOCUMENT CODE "CodeGenerator.cpp"
CREATION DATE 2017-11-09
SIGNATURE CODE_20171109_CODEGENERATOR
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20171109_CODEGENERATOR

#include <cstdlib>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>

#include <Windows.h>

using namespace std;
using namespace sfg;

class StringParser {
public:

	//将多个字符串以seperator为分隔符合并为一个
	static const string combineString(vector<string>& strings, char seperator) {
		if (strings.size() == 0)
			return "";
		string buffer = "";
		ostringstream out(buffer);
		out << strings[0];
		for (int i = 1; i < strings.size(); i++)
			out << seperator << strings[i];
		out.flush();
		return buffer;
	}

	//将按上述方法合并为一个字符串的多个字符串分开放到result里面
	static const void seperateString(string source, char seperator, vector<string>& result) {
		int get;
		string buffer;
		istringstream in(source);
		result.clear();
		while (true) {
			buffer.clear();
			while ((get = in.get())) {
				if (in.eof() || get == seperator)
					break;
				else
					buffer += char(get);
			}
			result.push_back(buffer);
			if (in.eof())
				break;
		}
	}

	template<typename... Args>
	static const string generateFormattedString(string source, Args... args) {
		char buffer[4096];
		sprintf_s(buffer, 4096, source.c_str(), args...);
		return string(buffer);
	}

	//把所有pair.first替换成pair.second
	static const string replaceSubString(string source, vector<pair<string, string> > replace) {
		string dest;

		for (pair<string, string> i : replace) {
			dest = ""s;
			for (int j = 0; j < source.size();) {
				if (source.substr(j, i.first.size()) == i.first) {
					j += i.first.size();
					dest += i.second;
				}
				else {
					dest += source[j];
					j++;
				}
			}
			source = dest;
		}
		return source;
	}

	//将各种整数/浮点数转换为字符串
	//或者考虑std::to_string()??? 
	static const string toString(bool                   data) { char buff[48]; sprintf(buff, "%d", data);   return string(buff); }
	static const string toString(short                  data) { char buff[48]; sprintf(buff, "%d", data);   return string(buff); }
	static const string toString(unsigned short         data) { char buff[48]; sprintf(buff, "%d", data);   return string(buff); }
	static const string toString(int                    data) { char buff[48]; sprintf(buff, "%d", data);   return string(buff); }
	static const string toString(unsigned int           data) { char buff[48]; sprintf(buff, "%u", data);   return string(buff); }
	static const string toString(long long              data) { char buff[48]; sprintf(buff, "%lld", data); return string(buff); }
	static const string toString(unsigned long long     data) { char buff[48]; sprintf(buff, "%llu", data); return string(buff); }
	static const string toString(float                  data) { char buff[48]; sprintf(buff, "%f", data);   return string(buff); }
	static const string toString(double                 data) { char buff[48]; sprintf(buff, "%lf", data);  return string(buff); }

	//将字符串转换为各种整数/浮点数
	static const bool      toBool(string&     data) { int x;       sscanf(data.c_str(), "%d", &x);   return x; }
	static const short     toShort(string&    data) { int x;       sscanf(data.c_str(), "%d", &x);   return x; }
	static const int       toInt(string&      data) { int x;       sscanf(data.c_str(), "%d", &x);   return x; }
	static const long long toLongLong(string& data) { long long x; sscanf(data.c_str(), "%lld", &x); return x; }
	static const float     toFloat(string&    data) { float x;     sscanf(data.c_str(), "%f", &x);   return x; }
	static const double    toDouble(string&   data) { double x;    sscanf(data.c_str(), "%lf", &x);  return x; }

};

typedef sf::Rect<sf::Uint32> UintRect;
typedef pair<string, string> StringPair;

const char code[] = { "/*\r\n"
"DOCUMENT CODE \"%filename%\"\r\n"
"CREATION DATE %date-brakes%\r\n"
"SIGNATURE CODE_%date%_%filecode-uppercase%\r\n"
"TOPIC %topic%\r\n"
"*/\r\n"
"\r\n"
"#include \"Overall.hpp\"\r\n"
"\r\n"
"//Check if this code file is enabled for testing.\r\n"
"#ifdef CODE_%date%_%filecode-uppercase%\r\n"
"\r\n"
"#include <cstdlib>\r\n"
"#include <iostream>\r\n"
"using namespace std;\r\n"
"\r\n"
"int main(int argc, char* argv[]) {\r\n"
"	\r\n"
"	return 0;\r\n"
"}\r\n"
"\r\n"
"#endif\r\n"
"\r\n" };

const string toUpperCase(string str) {
	for (char& i : str) {
		i = toupper(i);
	}
	return str;
}

const sf::String Gb18030ToUnicode(const string str) {
	wchar_t* buffer = new wchar_t[str.size() + 2];
	MultiByteToWideChar(54936, 0, str.c_str(), -1, buffer, str.size());
	buffer[str.size()] = '\0';
	return sf::String(buffer);
}

void setWindowsTheme(Desktop&);

sf::Font msyh;

const float getHighDpiScaleFactor(sf::RenderWindow& win = sf::RenderWindow()) {
	UINT dpi = 96;
	DPI_AWARENESS dpiAwareness = GetAwarenessFromDpiAwarenessContext(GetThreadDpiAwarenessContext());
	switch (dpiAwareness) {
		// Scale the window to the system DPI
	case DPI_AWARENESS_SYSTEM_AWARE:
		dpi = GetDpiForSystem();
		break;

		// Scale the window to the monitor DPI
	case DPI_AWARENESS_PER_MONITOR_AWARE:
		dpi = GetDpiForWindow(win.getSystemHandle());
		break;
	}

	return dpi / 96.0f;
}

int main(int argc, char* argv[]) {

	SFGUI sfgui;

	Desktop desktop;

	desktop.SetProperty("*", "FontSize", 12 * getHighDpiScaleFactor());
	//msyh.loadFromFile(getenv("windir") + string("\\Fonts\\msyh.ttc"));
	//desktop.GetEngine().GetResourceManager().SetDefaultFont(make_shared<sf::Font>(msyh));

	//setWindowsTheme(desktop);

	sf::RenderWindow win;

	time_t ttime = time(NULL);
	int dateYear = localtime(&ttime)->tm_year + 1900,
		dateMonth = localtime(&ttime)->tm_mon + 1,
		dateDay = localtime(&ttime)->tm_mday;

	Window::Ptr mainWin = Window::Create(Window::BACKGROUND);
	mainWin->SetRequisition(sf::Vector2f(400.0f, 0.0f));

	Table::Ptr mainTable = Table::Create();

	Entry::Ptr fileCodeEntry = Entry::Create(), commentEntry = Entry::Create();
	Entry::Ptr filenameEntry = Entry::Create(), signatureEntry = Entry::Create();

	Frame::Ptr codeFrame = Frame::Create(L"Code Preview");
	Label::Ptr codeLabel = Label::Create();

	Table::Ptr buttonTable = Table::Create();
	Button::Ptr copyFilenameButton = Button::Create(L"Copy filename");
	Button::Ptr copyCodeButton = Button::Create(L"Copy Code");
	Button::Ptr copySignButton = Button::Create(L"Copy Signature");

	function<void()> updateCode, updateFilename = [&]() {
		filenameEntry->SetText(StringParser::generateFormattedString("%04d%02d%02d-%s.cpp",
			dateYear, dateMonth, dateDay, fileCodeEntry->GetText().toAnsiString().c_str()));
	}, updateSignature = [&]() {
		signatureEntry->SetText(StringParser::generateFormattedString("CODE_%04d%02d%02d_%s",
			dateYear, dateMonth, dateDay, toUpperCase(fileCodeEntry->GetText().toAnsiString()).c_str()));
	};
	updateCode = [&]() {
		updateFilename();
		updateSignature();

		codeLabel->SetText(Gb18030ToUnicode(StringParser::replaceSubString(code, vector<StringPair>({
			StringPair("%filename%",filenameEntry->GetText()),
			StringPair("%filecode-uppercase%",toUpperCase(fileCodeEntry->GetText().toAnsiString())),
			StringPair("%date%",StringParser::generateFormattedString("%04d%02d%02d",dateYear, dateMonth, dateDay)),
			StringPair("%date-brakes%",StringParser::generateFormattedString("%04d-%02d-%02d",dateYear, dateMonth, dateDay)),
			StringPair("%topic%",commentEntry->GetText().toAnsiString())
		}))));

		mainTable->RefreshAll();
	};

	mainTable->SetColumnSpacings(5.0f);
	mainTable->SetRowSpacings(5.0f);

	mainTable->Attach(Label::Create(L"Date"), UintRect(0, 0, 1, 1), Table::FILL, Table::FILL);
	mainTable->Attach(Label::Create(StringParser::generateFormattedString("%d-%d-%d", dateYear, dateMonth, dateDay)),
		UintRect(1, 0, 7, 1), Table::FILL | Table::EXPAND, Table::FILL);

	mainTable->Attach(Label::Create(L"File Code"), UintRect(0, 1, 1, 1), Table::FILL, Table::FILL);
	mainTable->Attach(fileCodeEntry, UintRect(1, 1, 7, 1), Table::FILL | Table::EXPAND, Table::FILL);
	fileCodeEntry->GetSignal(Entry::OnTextChanged).Connect(updateCode);

	mainTable->Attach(Label::Create(L"Comment"), UintRect(0, 2, 1, 1), Table::FILL, Table::FILL);
	mainTable->Attach(commentEntry, UintRect(1, 2, 7, 1), Table::FILL | Table::EXPAND, Table::FILL);
	commentEntry->GetSignal(Entry::OnTextChanged).Connect(updateCode);

	mainTable->Attach(Separator::Create(), UintRect(0, 3, 8, 1), Table::FILL | Table::EXPAND, Table::FILL, sf::Vector2f(8.0f, 8.0f));

	mainTable->Attach(Label::Create(L"File Name"), UintRect(0, 4, 1, 1), Table::FILL, Table::FILL);
	mainTable->Attach(filenameEntry, UintRect(1, 4, 7, 1), Table::FILL | Table::EXPAND, Table::FILL);

	mainTable->Attach(Label::Create(L"Signature"), UintRect(0, 5, 1, 1), Table::FILL, Table::FILL);
	mainTable->Attach(signatureEntry, UintRect(1, 5, 7, 1), Table::FILL | Table::EXPAND, Table::FILL);

	mainTable->Attach(Separator::Create(), UintRect(0, 6, 8, 1), Table::FILL | Table::EXPAND, Table::FILL, sf::Vector2f(8.0f, 8.0f));

	buttonTable->Attach(copyFilenameButton, UintRect(0, 0, 1, 1));
	copyFilenameButton->GetSignal(Button::OnLeftClick).Connect([&]() {
		sf::Clipboard::setString(filenameEntry->GetText());
	});
	buttonTable->Attach(copyCodeButton, UintRect(0, 1, 2, 1));
	copyCodeButton->GetSignal(Button::OnLeftClick).Connect([&]() {
		sf::Clipboard::setString(codeLabel->GetText());
	});
	buttonTable->Attach(copySignButton, UintRect(1, 0, 1, 1));
	copySignButton->GetSignal(Button::OnLeftClick).Connect([&]() {
		sf::Clipboard::setString(signatureEntry->GetText());
	});

	buttonTable->SetColumnSpacings(2.0f);
	buttonTable->SetRowSpacings(5.0f);

	mainTable->Attach(buttonTable, UintRect(0, 7, 8, 1), Table::FILL, Table::EXPAND | Table::FILL, sf::Vector2f(8.0f, 8.0f));

	mainWin->Add(mainTable);
	mainWin->GetSignal(Window::OnSizeAllocate).Connect([&]() {
		win.setSize(sf::Vector2u(mainWin->GetAllocation().width, mainWin->GetAllocation().height));
	});

	desktop.Add(mainWin);

	win.create(sf::VideoMode(mainWin->GetAllocation().width, mainWin->GetAllocation().height),
		"Code Template", sf::Style::Titlebar | sf::Style::Close);
	win.setFramerateLimit(120);
	win.setVerticalSyncEnabled(true);
	win.clear(sf::Color(240, 240, 240));
	win.display();

	desktop.Update(1.0f);

	sf::Event event;
	sf::Clock logicClock;
	win.resetGLStates();
	while (win.isOpen()) {

		desktop.Update(logicClock.restart().asSeconds());

		win.clear();
		sfgui.Display(win);
		win.display();

		while (win.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				win.close();
			else
				desktop.HandleEvent(event);
		}
	}

	return 0;
}


void setWindowsTheme(Desktop& desktop) {
	desktop.GetEngine().ClearProperties();

	// Set defaults.
	desktop.SetProperty("*", "Color", sf::Color(0x00, 0x00, 0x00));
	desktop.SetProperty("*", "FontSize", 12);
	desktop.SetProperty("*", "FontName", "Default"); // Use default SFGUI font when available.
	desktop.SetProperty("*", "BackgroundColor", sf::Color(0xff, 0xff, 0xff));
	desktop.SetProperty("*", "BorderColor", sf::Color(0xad, 0xad, 0xad));
	desktop.SetProperty("*", "BorderColorShift", 0);
	desktop.SetProperty("*", "BorderWidth", 1.f);
	desktop.SetProperty("*", "Padding", 5.f);
	desktop.SetProperty("*", "Thickness", 2.f);

	// Window-specific.
	desktop.SetProperty("Window", "Gap", 10.f);
	desktop.SetProperty("Window", "BorderColor", sf::Color(0xc0, 0xc0, 0xc0));
	desktop.SetProperty("Window", "BorderColorShift", 0);
	desktop.SetProperty("Window", "BackgroundColor", sf::Color(240, 240, 240));
	desktop.SetProperty("Window", "TitleBackgroundColor", sf::Color(0xff, 0xff, 0xff));
	desktop.SetProperty("Window", "TitlePadding", 5.f);
	desktop.SetProperty("Window", "HandleSize", 10.f);
	desktop.SetProperty("Window", "ShadowDistance", 3.f);
	desktop.SetProperty("Window", "ShadowAlpha", 100.f);
	desktop.SetProperty("Window", "CloseHeight", 10.f);
	desktop.SetProperty("Window", "CloseThickness", 3.f);

	// Button-specific.
	desktop.SetProperty("Button", "BackgroundColor", sf::Color(0xe1, 0xe1, 0xe1));
	desktop.SetProperty("Button", "BorderColor", sf::Color(0xad, 0xad, 0xad));
	desktop.SetProperty("Button", "Spacing", 5.f);
	desktop.SetProperty("Button:PRELIGHT", "BackgroundColor", sf::Color(0xe5, 0xf1, 0xfb));
	desktop.SetProperty("Button:PRELIGHT", "Color", sf::Color::Black);
	desktop.SetProperty("Button:PRELIGHT", "BorderColor", sf::Color(0, 120, 215));
	desktop.SetProperty("Button:ACTIVE", "BackgroundColor", sf::Color(204, 228, 247));
	desktop.SetProperty("Button:ACTIVE", "Color", sf::Color::Black);
	desktop.SetProperty("Button:ACTIVE", "BorderColor", sf::Color(0, 84, 153));

	// ToggleButton-specific.
	desktop.SetProperty("ToggleButton", "BackgroundColor", sf::Color(255, 255, 255));
	desktop.SetProperty("ToggleButton", "BorderColor", sf::Color(0xad, 0xad, 0xad));
	desktop.SetProperty("ToggleButton", "Padding", 5.f);
	desktop.SetProperty("ToggleButton:PRELIGHT", "Color", sf::Color::White);
	desktop.SetProperty("ToggleButton:PRELIGHT", "BorderColor", sf::Color(0, 120, 215));
	desktop.SetProperty("ToggleButton:ACTIVE", "Color", sf::Color::Black);
	desktop.SetProperty("ToggleButton:ACTIVE", "BorderColor", sf::Color(0, 84, 153));

	// CheckButton-specific.
	desktop.SetProperty("CheckButton", "Spacing", 5.f);
	desktop.SetProperty("CheckButton", "CheckSize", 6.f);
	desktop.SetProperty("CheckButton", "BorderColor", sf::Color(0xad, 0xad, 0xad));
	desktop.SetProperty("CheckButton", "BackgroundColor", sf::Color(255, 255, 255));
	desktop.SetProperty("CheckButton", "CheckColor", sf::Color(0, 0, 0));
	desktop.SetProperty("CheckButton:PRELIGHT", "BorderColor", sf::Color(0, 120, 215));
	desktop.SetProperty("CheckButton:ACTIVE", "BorderColor", sf::Color(0, 84, 153));

	// RadioButton-specific.
	desktop.SetProperty("RadioButton", "Spacing", 5.f);
	desktop.SetProperty("RadioButton", "BoxSize", 14.f);
	desktop.SetProperty("RadioButton", "CheckSize", 6.f);
	desktop.SetProperty("RadioButton", "BorderColor", sf::Color(0xad, 0xad, 0xad));
	desktop.SetProperty("RadioButton", "BackgroundColor", sf::Color(255, 255, 255));
	desktop.SetProperty("RadioButton", "CheckColor", sf::Color(0, 0, 0));
	desktop.SetProperty("RadioButton:PRELIGHT", "BackgroundColor", sf::Color(0xe5, 0xf1, 0xfb));
	desktop.SetProperty("RadioButton:PRELIGHT", "Color", sf::Color::Black);
	desktop.SetProperty("RadioButton:PRELIGHT", "BorderColor", sf::Color(0, 120, 215));
	desktop.SetProperty("RadioButton:ACTIVE", "BackgroundColor", sf::Color(204, 228, 247));
	desktop.SetProperty("RadioButton:ACTIVE", "Color", sf::Color::Black);
	desktop.SetProperty("RadioButton:ACTIVE", "BorderColor", sf::Color(0, 84, 153));

	// Entry-specific.
	desktop.SetProperty("Entry", "BackgroundColor", sf::Color(255, 255, 255));
	desktop.SetProperty("Entry", "Color", sf::Color::Black);

	// Scale-specific.
	desktop.SetProperty("Scale", "SliderColor", sf::Color(128, 128, 128));
	desktop.SetProperty("Scale", "SliderLength", 15.f);
	desktop.SetProperty("Scale", "TroughColor", sf::Color(192, 192, 192));
	desktop.SetProperty("Scale", "TroughWidth", 5.f);

	// Scrollbar-specific.
	desktop.SetProperty("Scrollbar", "BackgroundColor", sf::Color(240, 240, 240));
	desktop.SetProperty("Scrollbar", "SliderColor", sf::Color(0x70, 0x70, 0x70));
	desktop.SetProperty("Scrollbar", "TroughColor", sf::Color(205, 205, 205));
	desktop.SetProperty("Scrollbar", "StepperBackgroundColor", sf::Color(240, 240, 240));
	desktop.SetProperty("Scrollbar", "StepperArrowColor", sf::Color(96, 96, 96));
	desktop.SetProperty("Scrollbar", "StepperSpeed", 10.f);
	desktop.SetProperty("Scrollbar", "StepperRepeatDelay", 300);
	desktop.SetProperty("Scrollbar", "SliderMinimumLength", 15.f);

	// ScrolledWindow-specific.
	desktop.SetProperty("ScrolledWindow", "ScrollbarWidth", 20.f);
	desktop.SetProperty("ScrolledWindow", "ScrollbarSpacing", 5.f);
	desktop.SetProperty("ScrolledWindow", "BorderColor", sf::Color(96, 96, 96));
	desktop.SetProperty("ScrolledWindow", "BackgroundColor", sf::Color(255, 255, 255));

	// ProgressBar-specific.
	desktop.SetProperty("ProgressBar", "BackgroundColor", sf::Color(240, 240, 240));
	desktop.SetProperty("ProgressBar", "BorderColor", sf::Color(240, 240, 240));
	desktop.SetProperty("ProgressBar", "BarColor", sf::Color(0, 120, 215));
	desktop.SetProperty("ProgressBar", "BarBorderColor", sf::Color(0, 120, 215));
	desktop.SetProperty("ProgressBar", "BarBorderColorShift", 0);
	desktop.SetProperty("ProgressBar", "BarBorderWidth", .5f);

	// Separator-specific.
	desktop.SetProperty("Separator", "Color", sf::Color(0xad, 0xad, 0xad));

	// Frame-specific.
	desktop.SetProperty("Frame", "BorderColor", sf::Color(0xad, 0xad, 0xad));
	desktop.SetProperty("Frame", "Padding", 7.f);
	desktop.SetProperty("Frame", "LabelPadding", 5.f);

	// Notebook-specific.
	desktop.SetProperty("Notebook", "BorderColor", sf::Color(173, 173, 173));
	desktop.SetProperty("Notebook", "BackgroundColorDark", sf::Color(240, 240, 240));
	desktop.SetProperty("Notebook", "BackgroundColorPrelight", sf::Color(229, 241, 251));
	desktop.SetProperty("Notebook", "ScrollButtonSize", 20.f);
	desktop.SetProperty("Notebook", "ScrollButtonPrelightColor", sf::Color(229, 241, 251));
	desktop.SetProperty("Notebook", "ScrollSpeed", 2.f);

	// Spinner-specific.
	desktop.SetProperty("Spinner", "CycleDuration", 800.f);
	desktop.SetProperty("Spinner", "Steps", 13);
	desktop.SetProperty("Spinner", "StoppedAlpha", 47);
	desktop.SetProperty("Spinner", "InnerRadius", 8.f);
	desktop.SetProperty("Spinner", "RodThickness", 3.f);

	// ComboBox-specific.
	desktop.SetProperty("ComboBox", "HighlightedColor", sf::Color(229, 241, 251));
	desktop.SetProperty("ComboBox", "ArrowColor", sf::Color(96, 96, 96));
	desktop.SetProperty("ComboBox", "ItemPadding", 4.f);
	desktop.SetProperty("ComboBox:PRELIGHT", "BackgroundColor", sf::Color(204, 228, 247));
	desktop.SetProperty("ComboBox:ACTIVE", "BackgroundColor", sf::Color(204, 228, 247));

	// SpinButton-specific.
	desktop.SetProperty("SpinButton", "BackgroundColor", sf::Color::White);
	desktop.SetProperty("SpinButton", "Color", sf::Color::Black);
	desktop.SetProperty("SpinButton", "StepperAspectRatio", 1.2f);
	desktop.SetProperty("SpinButton", "StepperBackgroundColor", sf::Color(240, 240, 240));
	desktop.SetProperty("SpinButton", "StepperArrowColor", sf::Color(96, 96, 96));
	desktop.SetProperty("SpinButton", "StepperSpeed", 10.f);
	desktop.SetProperty("SpinButton", "StepperRepeatDelay", 500);
}


#endif
