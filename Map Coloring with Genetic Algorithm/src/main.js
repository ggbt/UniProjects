window.addEventListener( 'load', function () {

  var nrColors = 4;
  var nrCromozomi = 80;

  document.getElementById( 'nrCulori').innerHTML = 'Nr. culori: ' + nrColors;
  document.getElementById( 'nrCromozomi').innerHTML = 'Nr. cromozomi: ' + nrCromozomi;



  var judete = new JudeteRomania();
  var romaniaMap = new RomaniaMap( 'harta');
  var romaniaMap2 = new RomaniaMap( 'harta2');

  var geneticColoring = new GeneticMapColoring( judete, romaniaMap, romaniaMap2, nrColors);

  geneticColoring.solve( nrCromozomi);

}, false);