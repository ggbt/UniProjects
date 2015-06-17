var GeneticMapColoring = function ( judete, map, auxMap, nrColors) {

  this.colors = [ '#E34141', '#E3B21F', '#ED6212', '#3CBB75', '#A7C774', '#D3F35A', '#F54BA2', '#47CECE'];

  this.judete = [];
  for ( var judet in judete) {
    if ( judete.hasOwnProperty( judet)) {
      this.judete.push( judete[judet]);
    }
  }

  this.map = map;
  this.auxMap = auxMap;

  this.nrColors = nrColors || 8;
  this.nrColors = (this.nrColors < 4) ? 4 : this.nrColors;
  this.nrColors = (this.nrColors > this.colors.length) ? this.colors.length : this.nrColors;
};

GeneticMapColoring.prototype.solve = function ( nrCromozoms) {

  var generation = 1;

  var cromozomi = this.selection( nrCromozoms);
  var bestFitness = this.calculateFitness( cromozomi);

  var bestFitnessSoFar = 999;

  var loop = function () {

    this.incrucisare( cromozomi);
    this.mutatie( cromozomi);

    bestFitness = this.calculateFitness( cromozomi);
    generation++;

    display();

    if ( cromozomi[bestFitness].totalFitness > 0 && generation < 10000) {
      setTimeout( loop, 0);
    }

  }.bind( this);

  var display = function () {
    this.draw( cromozomi[bestFitness], this.map);
    document.getElementById( 'info1').innerHTML = 'generation: ' + generation + ' - best fitness: ' + cromozomi[bestFitness].totalFitness;

    if (bestFitnessSoFar > cromozomi[bestFitness].totalFitness) {
      bestFitnessSoFar = cromozomi[bestFitness].totalFitness;

      this.draw( cromozomi[bestFitness], this.auxMap);
      document.getElementById( 'info2').innerHTML = 'generation: ' + generation + ' - best fitness: ' + cromozomi[bestFitness].totalFitness;
    }
  }.bind(this);

  // start solving
  setTimeout( loop, 200);

};

GeneticMapColoring.prototype.selection = function ( nrCromozomi) {
  var cromozomi = new Array( nrCromozomi);

  for ( var i = 0; i < nrCromozomi; i++) {
    cromozomi[i] = [];
    for ( var j = 0; j < this.judete.length; j++) {
      var color = this.colors[getRandomInt( 0, this.nrColors)];
      cromozomi[i].push( {
        color: color,
        fitness: 0
      });
    }
    cromozomi[i].totalFitness = 0;
  }

  return cromozomi;
};

GeneticMapColoring.prototype.calculateFitness = function ( cromozomi) {

  var bestFitness = {
    value: 9999,
    position: -1
  };

  for ( var i = 0; i < cromozomi.length; i++) {
    var cromozom = cromozomi[i];
    cromozom.totalFitness = 0;

    for ( var j = 0; j < cromozom.length; j++) {
      var gena = cromozom[j];
      gena.fitness = 0;

      var vecini = this.judete[j].vecini;

      for ( var v= 0; v < vecini.length; v++) {
        var vecin = vecini[v];
        var vecinIndex = this.getVecinIndex( vecin.name);
        if ( cromozom[ vecinIndex].color === gena.color) {
          gena.fitness++;
          cromozom.totalFitness++;
        }
      }
    }

    if ( cromozom.totalFitness < bestFitness.value) {
      bestFitness.value = cromozom.totalFitness;
      bestFitness.position = i;
    }
  }

  return bestFitness.position;

};

GeneticMapColoring.prototype.getVecinIndex = function ( vecin) {
  var index = 0;

  for ( var i = 0; i < this.judete.length; i++) {
    if (this.judete[i].name === vecin ) {
      index = i;
      break;
    }
  }

  return index;
};

GeneticMapColoring.prototype.incrucisare = function ( cromozomi) {

  cromozomi.sort( function ( a, b) {
    if ( a.totalFitness > b.totalFitness) {
      return -1;
    } else if ( b.totalFitness > a.totalFitness) {
      return 1;
    }
    return 0;
  });

  for ( var i = 0; i < cromozomi.length / 2 + cromozomi.length / 4; i += 2) {
    this.cross( cromozomi[i], cromozomi[i + 1]);
  }

};

GeneticMapColoring.prototype.cross = function ( A, B) {
  var length = A.length;
  if (A.length != B.length) {
    throw new Error( 'Lungimile cromozomilor nu sunt egale');
  }

  // Taieturi
  var k1 = getRandomInt( 0, length);
  var k2 = getRandomInt( 0, length);

  if ( k2 < k1) {
    var temp = k2;
    k2 = k1;
    k1 = temp;
  }

  for ( var i = k1; i <= k2; i++) {
    var temp = A[i];
    A[i] = B[i];
    B[i] = temp;
  }

};

GeneticMapColoring.prototype.mutatie = function ( cromozomi) {
  for ( var i = 0; i < cromozomi.length; i++) {
    var cromozom = cromozomi[i];

    this.mutate( cromozom);
  }
};

GeneticMapColoring.prototype.mutate = function ( cromozom) {

  for ( var i = 0; i < cromozom.length; i++) {
    var gena = cromozom[i];

    var mutationChance = 10 * gena.fitness;
    var rollDice = getRandomInt( 0, 100);

    var willMutate = rollDice < mutationChance;

    if ( willMutate) {
      gena.color = this.colors[ getRandomInt( 0, this.nrColors)];
    }
  }
};

GeneticMapColoring.prototype.draw = function ( cromozom, map) {

  for ( var i = 0; i < cromozom.length; i++) {
    map.judete[this.judete[i].name].attr( {
      fill: cromozom[i].color,
      "stroke": "#5C1010"
    });
  }
};

/**
 * Returns a random integer between min and max
 */
function getRandomInt(min, max) {
  return Math.floor(Math.random() * (max - min)) + min;
}