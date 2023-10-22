import Tetris from './src/tetris.js';
import View from "./src/view.js";
import Control from "./src/control.js";

const element = document.querySelector('#root');
const tetris = new Tetris();
const view = new View(element, 480, 640, 20, 10);
const control = new Control(tetris, view);
window.tetris = tetris;
window.view = view;
window.control = control;



