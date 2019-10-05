global figImg
global figImgOrig
global figPlot;
global figHist;
fig = figure('Renderer', 'painters', 'Position', [0 0 1280 130]);
pan = uipanel(fig,'Position',[0.00 0.00 0.9999 0.9999]);
%%ctrl = uicontrol(pan,'Style','slider');
%ctr.Limits = [0 3];
%%ctr.Value = 1.5;
%%ctrl.Position = [300 390 300 20];
%%ctrl.Callback = @sliderMoved;
textLabel01 = uicontrol('Style','text');
textLabel01.Position = [8 80 60 30];
textLabel01.String = 'Image';
textLabel01.FontSize = 14;
global imgSelect
imgSelect = uicontrol('Style','popupmenu');
imgSelect.String = {'Lena01','Lena02','Lake'};
imgSelect.Position = [70 95 90 20];
imgSelect.FontSize = 14;
textLabel02 = uicontrol('Style','text');
textLabel02.Position = [160 80 140 30];
textLabel02.String = 'Value to apply';
textLabel02.FontSize = 14;
global textInput
textInput = uicontrol('Style','edit');
textInput.Position = [295 80 100 30];
textInput.FontSize = 14;
textInput.Callback = @textInputCallback;
textLabel03 = uicontrol('Style','text');
textLabel03.Position = [400 80 100 30];
textLabel03.String = 'Operation: ';
textLabel03.FontSize = 14;
global imgOperation
imgOperation = uicontrol('Style','popupmenu');
imgOperation.String = {'Gain','Contrast','Brightness','Gamma'};
imgOperation.Position = [500 95 130 20];
imgOperation.FontSize = 14;
global runButton
runButton = uicontrol('Style','pushbutton');
runButton.String = 'Apply';
runButton.Position = [650 75 60 45];
runButton.FontSize = 14;
runButton.Callback = @processImage;
%%cg = uigauge(pan,'Position',[100 100 120 120]);