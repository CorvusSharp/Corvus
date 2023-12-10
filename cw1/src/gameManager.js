import {mapManager} from "./mapManager.js";
import {soundManager} from "./soundManager.js";
import {eventManager} from "./eventManager.js";
import {spriteManager} from "./spriteManager.js";
import {physicManager} from "./physicManager.js";


class GameManager { // менеджер игры
    constructor() {
        this.entities = []; // объекты на карте
        this.player = null; // указатель на объект игрока
        this.enemies = []; // массив врагов
        this.killCount = 0;
        this.initGame();
        this.intervalId = null;
        this.level = 1;
        this.score = 0;

    }

    clear() {
        this.entities = [];
        this.player = null;
        this.enemies = [];
        this.killCount = 0;
        this.level = 2;
    }
    updateLvl(){
        this.level++;
    }

    initGame() {
        this.killCount = 0;
        this.initPlayer();

    }


    initPlayer(obj) { // инициализация игрока
        this.player = obj;
    }

    initEnemy(obj) { // инициализация врага
        this.enemies.push(obj); // добавление врага в массив
    }

    draw(ctx) {
        for (let e = 0; e < this.entities.length; e++) {
            this.entities[e].draw(ctx)
        }
    }

    speedBonus() {
        this.player.speed += 1;
    }

    damageBonus() {
        this.player.damage += 5;
    }


    enemyAttack() {
        this.player.health -= 1;
    }


    update(ctx) {
        if (this.player === null) {
            return;
        }

        // Получение текущих направлений движения и скорости
        this.player.move_x = 0;
        this.player.move_y = 0;

        if (eventManager.action["up"]) {
            this.player.move_y = -this.player.speed;
        }
        if (eventManager.action["down"]) {
            this.player.move_y = this.player.speed;
        }
        if (eventManager.action["left"]) {
            this.player.move_x = -this.player.speed;
        }
        if (eventManager.action["right"]) {
            this.player.move_x = this.player.speed;
        }
        if (eventManager.action["attack"]) {
            this.player.attacking = true;
            eventManager.action["attack"] = false;
        }

        // Предполагаемое новое положение игрока
        let newX = this.player.pos_x + this.player.move_x;
        let newY = this.player.pos_y + this.player.move_y;

        // Проверка на столкновение перед обновлением позиции игрока
        if (!physicManager.hasCollision(this.player, newX, newY)) {
            // Если столкновения нет, обновляем позицию игрока
            this.player.pos_x = newX;
            this.player.pos_y = newY;
        }

        // Обновление и отрисовка всех сущностей
        this.entities.forEach(e => {
            if (e.update) {
                e.update(); // Вызов метода update для каждой сущности, если он существует
            }
        });

        mapManager.draw(ctx);
        this.draw(ctx);
    }


    loadAll(level, ctx) {
        if (level === 1) {
            mapManager.loadMap("maps/map1.json")
        }
        else if (level === 2){
            mapManager.loadMap("maps/map2.json")
        }
        if (level === 1)  {
               soundManager.loadArray(["maps/game.mp3"])
               soundManager.play("maps/game.mp3", {looping: false, volume: 0.2})
        }
        spriteManager.loadAtlas("maps/sprites.json", "maps/spritesheet.png")
        mapManager.parseEntities() // разбор сущностей карты
        mapManager.draw(ctx) // отобразить карту
        eventManager.setup() // настройка событий
    }

    play(ctx) {
        if (this.intervalId) {
            clearInterval(this.intervalId); // Остановить предыдущий интервал, если он существует
        }
        this.intervalId = setInterval(() => {
            this.update(ctx);
        }, 100);
    }

    stop() {
        if (this.intervalId) {
            clearInterval(this.intervalId); // Остановить интервал
            this.intervalId = null;
        }
    }



    addPlayerToTable(playerName, score) {
        var table = document.getElementById('score-table').getElementsByTagName('tbody')[0];
        var existingRow = [...table.rows].find(row => row.cells[0].textContent === playerName);

        if (!existingRow) {
            // Создаем новую строку и ячейки
            var newRow = table.insertRow(table.rows.length);
            var nameCell = newRow.insertCell(0);
            var scoreCell = newRow.insertCell(1);

            // Добавляем текст в ячейки
            nameCell.innerHTML = playerName;
            scoreCell.innerHTML = score;
        } else {
            // Обновляем существующую строку
            existingRow.cells[1].innerHTML = score;
        }
    }

    increaseKillCount() {
        this.killCount++;
        this.score ++;
        console.log(this.level)
        console.log(`Убито врагов: ${this.score}`);

        const currentPlayerName = localStorage.getItem('lastPlayerName');
        let players = JSON.parse(localStorage.getItem('players')) || {};

        if (currentPlayerName) {
            if (!players[currentPlayerName]) {
                players[currentPlayerName] = { score: 0 };
            }
            players[currentPlayerName].score = this.score;
            localStorage.setItem('players', JSON.stringify(players));

            this.addPlayerToTable(currentPlayerName, this.score); // Обновляем таблицу
        }

        if (this.killCount === 4 && this.level === 1)  {
            this.showLevelCompleteMenu();
        }
        else if (this.killCount === 12 && this.level === 2) {
           this.showTable();
        }
    }



    checkPlayerHealth() {
        if (this.player.health <= 0) {
            console.log('Игрок убит!');
            this.showTable();
        }

    }

    showTable() {
        const scoreTable = document.getElementById('score-section');
        const currentPlayerName = localStorage.getItem('lastPlayerName');
        let players = JSON.parse(localStorage.getItem('players')) || {};

        if (currentPlayerName && !players[currentPlayerName]) {
            this.addPlayerToTable(currentPlayerName, this.killCount);
        }

        console.log('Показ таблицы');
        if (scoreTable) {
            scoreTable.style.display = 'block';
        }
    }


    showLevelCompleteMenu() {
        const menu = document.getElementById('level-complete-menu');
        if (menu) {
            menu.style.display = 'block';
        }
    }


}

export const gameManager = new GameManager()

document.addEventListener('DOMContentLoaded', function() {
    let players = JSON.parse(localStorage.getItem('players')) || {};

    Object.keys(players).forEach(function(playerName) {
        const playerScore = players[playerName].score;
        gameManager.addPlayerToTable(playerName, playerScore);
    });
});

document.getElementById('restart-button').addEventListener('click', () => {
    window.location.href = 'index.html';
});