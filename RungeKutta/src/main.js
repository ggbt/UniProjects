window.addEventListener('load', function () {

  // 20, -3, 2
  // 10, -10, 20
  // -15, -20, 15
  // 50, 21, 15

  view.init();
  rungeKutta( -12, 16, -30, 10000);

  /*for ( var i = 0; i < points.length; i++) {
    document.write( points[i].x + '  ' + points[i].y + '  ' + points[i].z + ' <br />');
  }*/


  // h e deltaT

}, false);