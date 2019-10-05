function processImage( src,event, handles  )
%PROCESSIMAGE Summary of this function goes here
%   Detailed explanation goes here
global textInput
value = textInput.String;
fprintf('textInput = %s\n',value);
global imgSelect
imgNum = imgSelect.Value;
fprintf('imgNum = %d\n',imgNum);
global imgOperation
operationNum = imgOperation.Value;
fprintf('imgOperation = %d\n',operationNum);
%%img;
switch imgNum
    case 1
        img = imread('C:/Lena01.jpg');
    case 2
        img = imread('C:/Lena02.jpg');
    case 3
        img = imread('C:/Lake.jpg');        
end;
global figPlot
try
close(figPlot);
catch err;
end
YUV = getYUV(double(img));
switch operationNum
    case 1
        val = str2double(value);
        YUV = powerLaw(YUV,val,1.0);    
    case 2
        val = str2num(value);
        YUV = contrast(YUV,val);
    case 3
        val = str2num(value);
        YUV = brightness(YUV,val); 
    case 4
        val = str2double(value);
        fprintf('performing gamma of %f\n',val);
        YUV = powerLaw(YUV,1,val);         
end;
RGB = getRGB(YUV);
showImg(RGB);
global figImgOrig
try
close(figImgOrig);
catch err;
end
figImgOrig = figure;
imshow(img);
set(figImgOrig,'Position', [0 50 681 642])
end

