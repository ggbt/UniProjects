var view = ( function () {

  function render() {
    // requestAnimationFrame( render);
    renderer.render( scene, camera);
  }

  function onWindowResize() {
    camera.aspect = window.innerWidth / window.innerHeight;
    camera.updateProjectionMatrix();

    renderer.setSize( window.innerWidth, window.innerHeight );
    render();
  }

  var renderer,
    scene,
    camera,
    controls;

  // init
  renderer = new THREE.WebGLRenderer();
  renderer.setSize( window.innerWidth, window.innerHeight);
  renderer.setClearColor( 0xF5F5F5, 0); // F7F7F7

  scene = new THREE.Scene();

  camera = new THREE.PerspectiveCamera( 75, window.innerWidth / window.innerHeight, 0.1, 10000);
  camera.position.z = 50;
  camera.position.z = 30;
  camera.position.z = 90;

  controls = new THREE.OrbitControls( camera, renderer.domElement);
  controls.rotateSpeed = 1.0;
  controls.zoomSpeed = 1.2;
  controls.panSpeed = 0.8;

  var initReady = false;
  var view = {};

  view.init = function () {
    document.body.appendChild( renderer.domElement);

    drawingTools.drawAxis( scene);
    drawingTools.drawLights( scene);

    // controls.addEventListener( 'change', render );
    window.addEventListener( 'resize', onWindowResize);

    initReady = true;
  };

  view.add = function ( point) {

    if ( !initReady) {
      return;
    }

    var dot = drawingTools.makeCube();

    dot.position.set( point.x, point.z, point.y);

    scene.add( dot);
  };

  view.addPoints = function ( points) {

    if ( !initReady) {
      return;
    }

    for ( var i = 0; i < points.length; i++) {
      var point = drawingTools.makeCube();

      point.position.set( points[i].x, points[i].z, points[i].y);

      scene.add( point);
    }
  };

  view.renderScene = function () {
    render();
  };

  return view;

})();

var drawingTools = ( function () {

  var drawingTools = {};

  var defaultScale = 0.3;

  var simpleMaterial = new THREE.MeshBasicMaterial( {color: 0x000000});
  var lambertMaterial = new THREE.MeshLambertMaterial( { color:0x838080, shading: THREE.FlatShading });

  var cubeGeometry = new THREE.BoxGeometry(1, 1, 1);
  var sphereGeometry = new THREE.SphereGeometry(1, 1, 1);

  drawingTools.makeParticle = function ( scale, material) {
    material = material || simpleMaterial;
    scale = scale || defaultScale;

    var particle = new THREE.Particle( material);

    particle.scale.x = scale;
    particle.scale.y = scale;
    particle.scale.z = scale;

    return particle;
  };

  drawingTools.makeCube = function ( scale, material) {
    material = material || lambertMaterial;
    scale = scale || defaultScale;

    var cube = new THREE.Mesh( cubeGeometry, material);

    cube.scale.x = scale;
    cube.scale.y = scale;
    cube.scale.z = scale;

    return cube;
  };

  drawingTools.makeSphere = function ( scale, material) {
    material = material || lambertMaterial;
    scale = scale || defaultScale;

    var sphere = new THREE.Mesh( sphereGeometry, material);

    sphere.scale.x = scale;
    sphere.scale.y = scale;
    sphere.scale.z = scale;

    return sphere;
  };

  drawingTools.drawAxis = function ( scene) {
    var axisSize = 300;
    var scale = 3;

    var OO = drawingTools.makeSphere( scale);
    OO.position.set( 0, 0, 0);
    var OX = drawingTools.makeSphere( scale);
    OX.position.set( axisSize, 0, 0);
    var OY = drawingTools.makeSphere( scale);
    OY.position.set( 0, axisSize, 0);
    var OZ = drawingTools.makeSphere( scale);
    OZ.position.set( 0, 0, axisSize);

    var geometry = new THREE.Geometry();
    geometry.vertices.push( OX.position);
    geometry.vertices.push( OO.position);
    geometry.vertices.push( OY.position);
    geometry.vertices.push( OO.position);
    geometry.vertices.push( OZ.position);

    var axis = new THREE.Line( geometry, new THREE.LineBasicMaterial( { color: 0xBB3737}));

    scene.add( axis);
    scene.add( OO);
    scene.add( OX);
    scene.add( OY);
    scene.add( OZ);
  };

  drawingTools.drawLights = function ( scene) {
    var light = new THREE.DirectionalLight( 0xCE664D );
    light.position.set( 5, 30, 20 );
    scene.add( light );

    light = new THREE.DirectionalLight( 0xF9646A );
    light.position.set( 2, 10, -1 );
    scene.add( light );

    light = new THREE.AmbientLight( 0xC0353B );
    scene.add( light );
  };

  return drawingTools;
})();