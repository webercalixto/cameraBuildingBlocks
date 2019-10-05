function imgOut  = brightness( img, bright )
Y=img(:,:,1);
U=img(:,:,2);
V=img(:,:,3);
Y = Y+bright;
vals = [1:1:255];
valsOut = vals;
valsOut=valsOut+bright;
valsOut(valsOut>255) = 255;
global figPlot
figPlot = figure(9);
sTitle = sprintf ('Y" = Y+%d \n',c,bright);
plot(vals,valsOut);
xlim([0 255])
ylim([0 300])
grid on
imgOut = cat(3,Y,U,V);
end

