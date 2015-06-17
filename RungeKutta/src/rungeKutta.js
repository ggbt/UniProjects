/**
 * Created by Gabriel Titerlea
 */

var rungeKutta = ( function () {

  var defaultNrSteps = 500;
  var h = 0.09;

  var rungeKutta = function ( x, y, z, nrSteps) {

    nrSteps = nrSteps || defaultNrSteps;
    h = 10 / nrSteps;

    if (nrSteps > 100) {
      h = 0.006;
    }

    var R = [ { x: x, y: y, z: z}];

    var k1, k2, k3, k4;


    var i = 0;

    var loop = function () {
      k1 = F({
        x: R[i].x,
        y: R[i].y,
        z: R[i].z
      });

      k2 = F({
        x: R[i].x + k1.x / 2,
        y: R[i].y + k1.y / 2,
        z: R[i].z + k1.z / 2
      });

      k3 = F({
        x: R[i].x + k2.x / 2,
        y: R[i].y + k2.y / 2,
        z: R[i].z + k2.z / 2
      });

      k4 = F({
        x: R[i].x + k3.x,
        y: R[i].y + k3.y,
        z: R[i].z + k3.z
      });

      R.push({
        x: R[i].x + 1 / 6 * ( k1.x + 2 * k2.x + 2 * k3.x + k4.x),
        y: R[i].y + 1 / 6 * ( k1.y + 2 * k2.y + 2 * k3.y + k4.y),
        z: R[i].z + 1 / 6 * ( k1.z + 2 * k2.z + 2 * k3.z + k4.z)
      });

      view.add( R[++i]);
      view.renderScene();

      if ( i <= nrSteps) {
        requestAnimationFrame( loop);
      }
    }

    loop();

    return R;
  };

  var gama = 10;
  var ro = 28;
  var beta = 8 / 3;

  var F = function ( point) {
    return {
      x: h * dxdt( point.x, point.y, point.z),
      y: h * dydt( point.x, point.y, point.z),
      z: h * dzdt( point.x, point.y, point.z)
    }
  };

  var dxdt = function ( x, y, z) {
    return gama * (y - x);
  };

  var dydt = function ( x, y, z) {
    return x * (ro - z) - y;
  };

  var dzdt = function ( x, y, z) {
    return x * y - beta * z;
  };

  return rungeKutta;
})();