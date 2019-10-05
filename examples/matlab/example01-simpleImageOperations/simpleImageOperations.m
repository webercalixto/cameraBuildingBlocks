global figImg
%%fig2 = figure;
fig = figure;
pan = uipanel(fig,'Position',[0.01 0.01 0.99 0.99]);
ctrl = uicontrol(pan,'Style','slider');
ctr.Value = 1.5;
ctrl.Position = [10 390 300 20];
ctrl.Callback = @sliderMoved;
%%cg = uigauge(pan,'Position',[100 100 120 120]);