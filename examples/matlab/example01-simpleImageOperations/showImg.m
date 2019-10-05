function showImg( img )
global figImg
try
close(figImg);
catch err;
end
figImg = figure;
img = img./255;
imshow(img);
end

