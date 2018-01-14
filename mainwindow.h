#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


#define PROGRAM_VERSION     "0.9.3"
#define SETTINGS_VENDOR     "ATutils"
#define SETTINGS_APP        "QuickEditor"
#define ENCODING_EA_NAME    ".CODEPAGE"

#if 0
#define DEFAULT_FILENAME_FILTERS                            \
    "Text files (*.txt readme*);;"                          \
    "Command files (*.cmd *.bat *.rex *.orx *.sh *.vrx);;"  \
    "All files (*)"
#else
#define DEFAULT_FILENAME_FILTERS                            \
    "Text files (*.txt readme*);;"                          \
    "Assembler source code (*.asm);;"                       \
    "BASIC source code (*.bas);;"                           \
    "C/C++ source code (*.c *.h *.cpp *.hpp *.cc);;"        \
    "Command files (*.cmd *.bat *.rex *.orx *.sh *.vrx);;"  \
    "Java source code (*.jav *.java);;"                     \
    "Pascal source code (*.pas);;"                          \
    "Python files (*.py);;"                                 \
    "WWW files (*.htm *.html *.css *.cgi *.js *.php);;"     \
    "All files (*)"
#endif

class QAction;
class QActionGroup;
class QLabel;
class QPlainTextEdit;
class QTextCursor;
class FindDialog;
class ReplaceDialog;

typedef struct _FindParams_t
{
    QString text;
    bool bCase;
    bool bWords;
    bool bBackward;
    bool bRe;
} FindParams;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    bool loadFile( const QString &fileName, bool createIfNew );
    void showUsage();
    void setReadOnly( bool readonly );

protected:
    void closeEvent( QCloseEvent *event );

private slots:
    void newFile();
    void open();
    bool save();
    bool saveAs();
    bool print();
    void find();
    void findAgain();
    void replace();
    void about();
    void openRecentFile();
    void clearRecentFiles();
    bool toggleEditMode( bool ovr );
    bool toggleReadOnly( bool readOnly );
    bool toggleWordWrap( bool bWrap );
    void updateStatusBar();
    void updateEncodingLabel();
    void updateModeLabel();
    void updatePositionLabel();
    void updateModified();
    void updateModified( bool isModified );
    void setEditorFont();
    void findNext( const QString &str, bool cs, bool words, bool fromStart );
    void findNextRegExp( const QString &str, bool cs, bool fromStart );
    void findPrevious( const QString &str, bool cs, bool words, bool fromEnd );
    void findPreviousRegExp( const QString &str, bool cs, bool fromEnd );
    void replaceNext( const QString &str, const QString &repl, bool cs, bool words, bool absolute, bool confirm );
    void replaceNextRegExp( const QString &str, const QString &repl, bool cs, bool absolute, bool confirm );
    void replacePrevious( const QString &str, const QString &repl, bool cs, bool words, bool absolute, bool confirm );
    void replacePreviousRegExp( const QString &str, const QString &repl, bool cs, bool absolute, bool confirm );
    void replaceAll( const QString &str, const QString &repl, bool cs, bool words, bool absolute, bool confirm, bool backwards );
    void replaceAllRegExp( const QString &str, const QString &repl, bool cs, bool absolute, bool confirm, bool backwards );
    void goToLine();
    void setTextEncoding();

private:
    // Setup methods
    void createActions();
    void createEncodingActions();
    void createMenus();
    void createContextMenu();
    void createStatusBar();
    void readSettings();
    void writeSettings();

    // Action methods
    bool okToContinue();
    bool saveFile( const QString &fileName );

    // Misc methods
    void setCurrentFile( const QString &fileName );
    void updateRecentFileActions();
    QString strippedName( const QString &fullFileName );
    void showMessage( const QString &message );
    void updateEncoding();
    bool showFindResult( QTextCursor found );
    bool replaceFindResult( QTextCursor found, const QString newText, bool confirm );
    QString getFileCodepage( const QString &fileName );
    void setFileCodepage( const QString &fileName, const QString &encodingName );

    // GUI objects
    QPlainTextEdit *editor;
    FindDialog *findDialog;
    ReplaceDialog *replaceDialog;

    QLabel *editModeLabel;
    QLabel *messagesLabel;
    QLabel *encodingLabel;
    QLabel *positionLabel;
    QLabel *modifiedLabel;

    enum { MaxRecentFiles = 5 };

    QMenu   *fileMenu;
    QAction *newAction;
    QAction *openAction;
    QAction *saveAction;
    QAction *saveAsAction;
    QAction *printAction;
    QAction *recentFileActions[ MaxRecentFiles ];
    QAction *clearRecentAction;
    QAction *separatorAction;
    QAction *exitAction;

    QMenu   *encodingMenu;
    QAction *localeAction;      // Default encoding for locale

    // Central/Eastern European
    QMenu   *centEuroMenu;
    QAction *iso88592Action;    // ISO 8859-2 (Latin-2)                 (codepage 912)
    QAction *win1250Action;     // Windows-1250 (MS Latin-2)            (codepage 1250)

    // Cyrillic
    QMenu   *cyrillicMenu;
    QAction *ibm866Action;      // IBM-866 (Russian)                    (codepage 866)
    QAction *iso88595Action;    // ISO 8859-5 (Cyrillic)                (codepage 915)
    QAction *koi8rAction;       // KOI8-R (Russian Internet encoding)   (codepage 878)
    QAction *koi8uAction;       // KOI8-U (Ukrainian Internet encoding) (codepage 1168)
    QAction *win1251Action;     // Windows-1251 (Cyrillic)              (codepage 1251)

    // East Asian
    QMenu   *eastAsiaMenu;
    QAction *big5Action;        // Big-5                                (codepage 950)
    QAction *gbAction;          // GBK/GB18030                          (codepage 1386)
    QAction *eucJpAction;       // EUC-JP                               (codepage 954)
    QAction *iso2022JpAction;   // ISO-2022-JP (Japanese mail encoding) (codepage 4992)
    QAction *sjisAction;        // Shift-JIS (codepage 932)             (codepage 932)
    QAction *eucKrAction;       // EUC-KR                               (codepage 970)

    // Middle Eastern
    QMenu   *midEastMenu;
    QAction *iso88596Action;    // ISO 8859-6 (Arabic)                  (codepage 1089)
    QAction *iso88598Action;    // ISO 8859-8 (Hebrew)                  (codepage 916)
    QAction *win1255Action;     // Windows-1255 (MS Hebrew)             (codepage 1255)
    QAction *win1256Action;     // Windows-1256 (MS Arabic)             (codepage 1256)

    // Northern European
    QMenu   *northEuroMenu;
    QAction *iso88594Action;    // ISO 8859-4 (Latin-4)                 (codepage 914)
    QAction *iso885910Action;   // ISO 8859-10 (Latin-6)                (codepage 919)
    QAction *iso885913Action;   // ISO 8859-13 (Latin-7)                (codepage 921)
    QAction *win1257Action;     // Windows-1257 (Baltic)                (codepage 1257)
    QAction *iso885914Action;   // ISO 8859-14 (Latin-8)                (no codepage - use 1090)

    // South Asian
    QMenu   *southAsiaMenu;
    QAction *tsciiAction;       // TSCII (Tamil)                        (no codepage - use 1092)
    QAction *ibm874Action;      // IBM-874 (Thai TIS-620)               (codepage 874)
    QAction *win1258Action;     // Windows-1258 (Vietnamese)            (codepage 1258)

    // Southern European
    QMenu   *southEuroMenu;
    QAction *iso88593Action;    // ISO 8859-3 (Latin-3)                 (codepage 913)
    QAction *iso88597Action;    // ISO 8859-7 (Greek)                   (codepage 813)
    QAction *win1253Action;     // Windows-1253 (MS Greek)              (codepage 1253)
    QAction *win1254Action;     // Windows-1254 (MS Latin-5)            (codepage 1254)
    QAction *iso885916Action;   // ISO 8859-16 (Latin-10)               (no codepage - use 1091)

    // Western European
    QMenu   *westEuroMenu;
    QAction *aromanAction;      // Apple Roman                          (codepage 1275)
    QAction *ibm850Action;      // IBM-850 (PC Latin-1)                 (codepage 850)
//    QAction *iso88591Action;    // ISO 8859-1 (Latin-1)                 (codepage 819)
    QAction *iso885915Action;   // ISO 8859-15 (Latin-9)                (codepage 923)
    QAction *win1252Action;     // Windows-1252 (MS Latin-1)            (codepage 1252)

    QMenu   *unicodeMenu;
    QAction *utf16Action;       // UTF-16 (LE)                          (codepage 1202)
    QAction *utf16beAction;     // UTF-16 (BE)                          (codepage 1200)
    QAction *utf8Action;        // UTF-8                                (codepage 1208)

    QActionGroup *encodingGroup;

    QMenu   *editMenu;
    QAction *undoAction;
    QAction *redoAction;
    QAction *cutAction;
    QAction *copyAction;
    QAction *pasteAction;
    QAction *selectAllAction;
    QAction *findAction;
    QAction *findAgainAction;
    QAction *replaceAction;
    QAction *goToAction;

    QMenu   *optionsMenu;
    QAction *wrapAction;
    QAction *editModeAction;
    QAction *readOnlyAction;
    QAction *fontAction;
    QAction *coloursAction;
    QAction *autosaveAction;

    QMenu   *helpMenu;
    QAction *aboutAction;

    // Other class variables

    QStringList recentFiles;
    QString     currentFile;
    QString     currentDir;
    QString     currentEncoding;
    bool        encodingChanged;
    int         lastGoTo;
    FindParams  lastFind;

};

#endif
