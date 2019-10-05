function showImg( img )
global figImg
try
close(figImg);
catch err;
end
figImg = figure;
img = img./255;
imshow(img);
set(figImg,'Position', [650 50 681 642])
end

