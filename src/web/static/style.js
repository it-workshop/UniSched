$(window).resize(function() {

console.log($('html').outerHeight(true));
//$('html').css('overflow', 'hidden');
//$('.tabs').css('height', $('html').outerHeight(true) - 25);
//$('.tabs').css('height', $('html').innerHeight() - 25);
$('.tabs').css('height', $('html').height() - 25);
//$('.frame').each(function(i, elem) {$(elem).css('height', $(elem).parent().outerHeight(true) - 93);});
$('.frame').each(function(i, elem) {$(elem).css('height', $(elem).parent().height() - 83);});
$('.column').each(function(i, elem) {$(elem).css('height', $(elem).parent().height() - 35);});
$('.accordion').accordion('resize');
});

$(document).ready(function() {$(window).resize()});
