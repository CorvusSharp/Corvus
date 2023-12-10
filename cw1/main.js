import {gameManager} from "./src/gameManager.js";
import {soundManager} from "./src/soundManager.js";
import {eventManager} from "./src/eventManager.js";
import {mapManager} from "./src/mapManager.js";
import {spriteManager} from "./src/spriteManager.js";


var canvas = document.getElementById("canvas");
var ctx = canvas.getContext("2d");
var lvl = 1;
soundManager.init();


function loadLevel(level) {
    gameManager.loadAll(level, ctx);
    gameManager.play(ctx);
}

loadLevel(lvl);

export function play (){
    eventManager.clear();
    gameManager.clear();
    mapManager.clear();
    spriteManager.clear();
    loadLevel(2);
    document.getElementById('level-complete-menu').style.display = 'none';

}


// Обработчик событий для кнопки перехода на следующий уровень
document.getElementById('next-level-button').addEventListener('click', () => {
    lvl++;
    console.log(lvl)
    console.log('Переход к следующему уровню...');
    document.getElementById('level-complete-menu').style.display = 'block';
});


