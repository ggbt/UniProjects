var JudeteRomania = function () {
  this.suceava = {color: '#FFFFFF', name: 'suceava'};
  this.botosani = {color: '#FFFFFF', name: 'botosani'};
  this.iasi = {color: '#FFFFFF', name: 'iasi'};
  this.neamt = {color: '#FFFFFF', name: 'neamt'};
  this.bacau = {color: '#FFFFFF', name: 'bacau'};
  this.vaslui = {color: '#FFFFFF', name: 'vaslui'};
  this.galati = {color: '#FFFFFF', name: 'galati'};
  this.vrancea = {color: '#FFFFFF', name: 'vrancea'};
  this.buzau = {color: '#FFFFFF', name: 'buzau'};
  this.braila = {color: '#FFFFFF', name: 'braila'};
  this.constanta = {color: '#FFFFFF', name: 'constanta'};
  this.tulcea = {color: '#FFFFFF', name: 'tulcea'};
  this.mehedinti = {color: '#FFFFFF', name: 'mehedinti'};
  this.dolj = {color: '#FFFFFF', name: 'dolj'};
  this.gorj = {color: '#FFFFFF', name: 'gorj'};
  this.valcea = {color: '#FFFFFF', name: 'valcea'};
  this.olt = {color: '#FFFFFF', name: 'olt'};
  this.arges = {color: '#FFFFFF', name: 'arges'};
  this.teleorman = {color: '#FFFFFF', name: 'teleorman'};
  this.dambovita = {color: '#FFFFFF', name: 'dambovita'};
  this.giurgiu = {color: '#FFFFFF', name: 'giurgiu'};
  this.ialomita = {color: '#FFFFFF', name: 'ialomita'};
  this.calarasi = {color: '#FFFFFF', name: 'calarasi'};
  this.prahova = {color: '#FFFFFF', name: 'prahova'};
  this.bucuresti  = {color: '#FFFFFF', name: 'bucuresti'};
  this.satu_mare = {color: '#FFFFFF', name: 'satu_mare'};
  this.maramures = {color: '#FFFFFF', name: 'maramures'};
  this.bihor = {color: '#FFFFFF', name: 'bihor'};
  this.arad = {color: '#FFFFFF', name: 'arad'};
  this.timis = {color: '#FFFFFF', name: 'timis'};
  this.caras_severin = {color: '#FFFFFF', name: 'caras_severin'};
  this.hunedoara = {color: '#FFFFFF', name: 'hunedoara'};
  this.alba = {color: '#FFFFFF', name: 'alba'};
  this.sibiu = {color: '#FFFFFF', name: 'sibiu'};
  this.brasov = {color: '#FFFFFF', name: 'brasov'};
  this.covasna = {color: '#FFFFFF', name: 'covasna'};
  this.harghita = {color: '#FFFFFF', name: 'harghita'};
  this.mures = {color: '#FFFFFF', name: 'mures'};
  this.bistrita_nasaud = {color: '#FFFFFF', name: 'bistrita_nasaud'};
  this.cluj = {color: '#FFFFFF', name: 'cluj'};
  this.salaj = {color: '#FFFFFF', name: 'salaj'};

  this.suceava.vecini = [
    this.maramures,
    this.bistrita_nasaud,
    this.mures,
    this.harghita,
    this.neamt,
    this.iasi,
    this.botosani
  ];

  this.botosani.vecini = [
    this.suceava,
    this.iasi
  ];

  this.iasi.vecini = [
    this.botosani,
    this.suceava,
    this.neamt,
    this.vaslui
  ];

  this.neamt.vecini = [
    this.suceava,
    this.harghita,
    this.bacau,
    this.vaslui,
    this.iasi
  ];

  this.bacau.vecini = [
    this.neamt,
    this.harghita,
    this.covasna,
    this.vrancea,
    this.vaslui
  ];

  this.vaslui.vecini = [
    this.iasi,
    this.neamt,
    this.bacau,
    this.vrancea,
    this.galati
  ];

  this.galati.vecini = [
    this.vaslui,
    this.vrancea,
    this.braila,
    this.tulcea
  ];

  this.vrancea.vecini = [
    this.bacau,
    this.covasna,
    this.buzau,
    this.braila,
    this.galati,
    this.vaslui
  ];

  this.buzau.vecini = [
    this.vrancea,
    this.covasna,
    this.brasov,
    this.prahova,
    this.ialomita,
    this.braila
  ];

  this.braila.vecini = [
    this.vrancea,
    this.buzau,
    this.ialomita,
    this.constanta,
    this.tulcea,
    this.galati
  ];

  this.constanta.vecini = [
    this.tulcea,
    this.braila,
    this.ialomita,
    this.calarasi
  ];

  this.tulcea.vecini = [
    this.galati,
    this.braila,
    this.constanta
  ];

  this.mehedinti.vecini = [
    this.caras_severin,
    this.gorj,
    this.dolj
  ];

  this.dolj.vecini = [
    this.mehedinti,
    this.gorj,
    this.valcea,
    this.olt
  ];

  this.gorj.vecini = [
    this.caras_severin,
    this.hunedoara,
    this.valcea,
    this.dolj,
    this.mehedinti
  ];

  this.valcea.vecini = [
    this.sibiu,
    this.alba,
    this.hunedoara,
    this.gorj,
    this.dolj,
    this.olt,
    this.arges
  ];

  this.olt.vecini = [
    this.dolj,
    this.valcea,
    this.arges,
    this.teleorman
  ];

  this.arges.vecini = [
    this.sibiu,
    this.valcea,
    this.olt,
    this.teleorman,
    this.dambovita,
    this.brasov
  ];

  this.teleorman.vecini = [
    this.olt,
    this.arges,
    this.dambovita,
    this.giurgiu
  ];

  this.dambovita.vecini = [
    this.brasov,
    this.arges,
    this.teleorman,
    this.giurgiu,
    this.bucuresti,
    this.prahova
  ];

  this.giurgiu.vecini = [
    this.teleorman,
    this.dambovita,
    this.bucuresti,
    this.calarasi
  ];

  this.ialomita.vecini = [
    this.buzau,
    this.prahova,
    this.bucuresti,
    this.calarasi,
    this.constanta,
    this.braila
  ];

  this.calarasi.vecini = [
    this.giurgiu,
    this.bucuresti,
    this.ialomita,
    this.constanta
  ];

  this.prahova.vecini = [
    this.brasov,
    this.dambovita,
    this.bucuresti,
    this.ialomita,
    this.buzau
  ];

  this.bucuresti.vecini = [
    this.prahova,
    this.dambovita,
    this.giurgiu,
    this.calarasi,
    this.ialomita
  ];

  this.satu_mare.vecini = [
    this.bihor,
    this.salaj,
    this.maramures
  ];

  this.maramures.vecini = [
    this.satu_mare,
    this.salaj,
    this.cluj,
    this.bistrita_nasaud,
    this.suceava
  ];

  this.bihor.vecini = [
    this.satu_mare,
    this.salaj,
    this.cluj,
    this.alba,
    this.arad
  ];

  this.arad.vecini = [
    this.bihor,
    this.alba,
    this.hunedoara,
    this.timis
  ];

  this.timis.vecini = [
    this.arad,
    this.hunedoara,
    this.caras_severin
  ];

  this.caras_severin.vecini = [
    this.timis,
    this.hunedoara,
    this.gorj,
    this.mehedinti
  ];

  this.hunedoara.vecini = [
    this.arad,
    this.timis,
    this.caras_severin,
    this.gorj,
    this.valcea,
    this.alba
  ];

  this.alba.vecini = [
    this.cluj,
    this.bihor,
    this.arad,
    this.hunedoara,
    this.valcea,
    this.sibiu,
    this.mures
  ];

  this.sibiu.vecini = [
    this.mures,
    this.alba,
    this.valcea,
    this.arad,
    this.brasov
  ];

  this.brasov.vecini = [
    this.harghita,
    this.mures,
    this.sibiu,
    this.arges,
    this.dambovita,
    this.prahova,
    this.buzau,
    this.covasna
  ];

  this.covasna.vecini = [
    this.harghita,
    this.brasov,
    this.buzau,
    this.vrancea,
    this.bacau
  ];

  this.harghita.vecini = [
    this.mures,
    this.brasov,
    this.covasna,
    this.bacau,
    this.neamt,
    this.suceava
  ];

  this.mures.vecini = [
    this.bistrita_nasaud,
    this.cluj,
    this.alba,
    this.sibiu,
    this.brasov,
    this.harghita,
    this.suceava
  ];

  this.bistrita_nasaud.vecini = [
    this.maramures,
    this.cluj,
    this.mures,
    this.suceava
  ];

  this.cluj.vecini = [
    this.salaj,
    this.bihor,
    this.alba,
    this.mures,
    this.bistrita_nasaud,
    this.maramures
  ];

  this.salaj.vecini = [
    this.satu_mare,
    this.bihor,
    this.cluj,
    this.maramures
  ];
};