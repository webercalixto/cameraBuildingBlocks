function [ imgOut ] = powerLaw( img, c, gamma )
Y=img(:,:,1);
U=img(:,:,2);
V=img(:,:,3);
Y=255*c*(Y/255).^(gamma);
if gamma == 1
    
else
    %%U = Y*0;
    %%V =Y*0;
end
vals = [1:1:255];
valsOut = vals;
valsOut=255*c*(valsOut/255).^(gamma);
valsOut(valsOut>255) = 255;
global figPlot
figPlot = figure(9);
sTitle = sprintf ('Y" = 255x%d(Y/255)^(%f) \n',c,gamma);
plot(vals,valsOut),title(sTitle);
xlim([0 255])
ylim([0 300])
grid on
imgOut = cat(3,Y,U,V);
end

