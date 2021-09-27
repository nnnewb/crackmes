import pefile
import wx
import wx.grid


class MyFrame(wx.Frame):
    def __init__(self, *args, **kw):
        super().__init__(*args, **kw)
        self.SetSizer(wx.BoxSizer(wx.VERTICAL))
        self.build_ui()
        self.Centre()

    def build_ui(self):
        # menubar
        mb = wx.MenuBar()
        mn = wx.Menu()
        mb.Append(mn, '文件')
        item = mn.Append(wx.ID_OPEN, '打开')
        self.SetMenuBar(mb)
        self.Bind(wx.EVT_MENU, self.on_open, item)

        # main panel
        panel = wx.Panel(self)
        vbox = wx.BoxSizer(wx.VERTICAL)

        self._grid = wx.grid.Grid(panel)
        self._grid.CreateGrid(1, 3)
        self._grid.SetColLabelValue(0, 'Section')
        self._grid.SetColLabelValue(1, 'VirtualSize')
        self._grid.SetColLabelValue(2, 'VirtualAddress')

        vbox.Add(self._grid, 1, wx.EXPAND)
        panel.SetSizer(vbox)

        self.Sizer.Add(panel, 1, wx.EXPAND | wx.LEFT | wx.RIGHT)

    def on_open(self, evt):
        dialog = wx.FileDialog(self)
        dialog.ShowModal()
        if dialog.Path:
            self.pe = pefile.PE(dialog.Path)
            self._grid.ClearGrid()
            self._grid.AppendRows(len(self.pe.sections))
            for idx, section in enumerate(self.pe.sections):
                self._grid.SetCellValue(idx, 0, section.Name.rstrip(b'\x00').decode())
                self._grid.SetCellValue(idx, 1, hex(section.Misc_VirtualSize))
                self._grid.SetCellValue(idx, 2, hex(section.VirtualAddress))


app = wx.App()
frm = MyFrame(None, title='frame')
frm.Show()
app.MainLoop()
