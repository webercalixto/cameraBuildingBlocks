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
end;
YUV = getYUV(double(img));
val = str2num(value);
YUV = brightness(YUV,val);
RGB = getRGB(YUV);
showImg(RGB);
global figImgOrig
try
close(figImgOrig);
catch err;
end
figImgOrig = figure;
imshow(img);
end

