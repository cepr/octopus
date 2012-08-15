import wx
import wx.wxsvg
import wxPython




     

class EditorFrame(wx.Frame):
    def __init__(self, titre):
        wx.Frame.__init__(self, None,-1, title = titre, size = (450, 350))
        self.myctrl = wx.wxsvg.SVGCtrl(self)
        

class DefEditor(wx.App):
    def OnInit(self):
        fen = EditorFrame("pywxsvg test")
        
        fen.myctrl.Load("test2.svg")
        fen.Show(True)

        self.Bind(wx.EVT_LEFT_DOWN, self.OnClick)
        
        #self.mydoc = wx.wxsvg.SVGDocument("tiger.svg")
        self.mydoc = fen.myctrl.GetSVG()
        self.myroot = self.mydoc.GetRootElement()
        rect = wx.wxsvg.SVGRect(50,50, 1, 1)
        win = wx.Window(fen)

        evt = wx.EvtHandler()

        #my_svgui_window = wx.wxsvg.SVGUIRotatingCtrl(self.mydoc,evt)
        
        #wxPython.wxDC(fen)

        
        self.SetTopWindow(fen)
        return True

    def OnClick(self,event):
        print "x => ",event.m_x,", y => ",event.m_y
        rect = wx.wxsvg.SVGRect(event.m_x,event.m_y, 1, 1)
        print self.GetIntersectionList(self.myroot,rect)

    def GetIntersectionList(self,_root,_rect):
        nodelist = _root.GetIntersectionList(_rect,_root)
        nodelistcls = wx.wxsvg.NodeListCls(nodelist)
        interTab = []
        i=0
        while i < nodelistcls.GetSize() :
          interTab.append(nodelistcls.GetElement(i).GetAttribute("id"))
          i = i+1
        return interTab

app = DefEditor()
app.MainLoop()


