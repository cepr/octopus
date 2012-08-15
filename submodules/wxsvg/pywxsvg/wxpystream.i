
%name(wxInputStream) class wxPyInputStream {
public:
    %addmethods {
        wxPyInputStream(PyObject* p) {
            wxInputStream* wxis = wxPyCBInputStream::create(p);
            if (wxis)
                return new wxPyInputStream(wxis);
            else
                return NULL;
        }
    }
    void close();
    void flush();
    bool eof();
    PyObject* read(int size=-1);
    PyObject* readline(int size=-1);
    PyObject* readlines(int sizehint=-1);
    void seek(int offset, int whence=0);
    int tell();

    /*
      bool isatty();
      int fileno();
      void truncate(int size=-1);
      void write(wxString data);
      void writelines(wxStringPtrList);
    */

    char Peek();
    char GetC();
    size_t LastRead();
    bool CanRead();
    bool Eof();
    bool Ungetch(char c);

    long SeekI(long pos, wxSeekMode mode = wxFromStart);
    long TellI();
}