import {physicManager} from "./physicManager.js";
import {spriteManager} from "./spriteManager.js";
import {gameManager} from "./gameManager.js";
import {mapManager} from "./mapManager.js";


class Entity {
    constructor() {
        this.name = ""
        this.pos_x = 0
        this.pos_y = 0
        this.size_x = 0
        this.size_y = 0
        this.type = ""
    }

    setName(name) {
        this.name = name
    }

    setPos_x(pos_x) {
        this.pos_x = pos_x
    }

    setPos_y(pos_y) {
        this.pos_y = pos_y
    }

    setSize_x(size_x) {
        this.size_x = size_x
    }

    setSize_y(size_y) {
        this.size_y = size_y
    }

    setType(type) {
        this.type = type
    }

    centreXY() {
        return {
            x: this.pos_x + this.size_x / 2,
            y: this.pos_y + this.size_y / 2
        };

    }

}

export class Enemy extends Entity {
    constructor() {
        super();
        this.health = 50;
        this.speed = 2;
        this.move_x = 0;
        this.move_y = 0;
        this.frame = 0; // Счетчик кадров для анимации
        this.animationSpeed = 1; // Скорость анимации (меньше значение - быстрее анимация)
        this.attacking = false;
        this.attackFrame = 0;
        this.totalAttackFrames = 4;
        this.totalRunFrames = 6;
        this.attackRange = 5;
    }

    draw(ctx) {
        if (this.attacking) {
            let attackSprite = `enemyAttack${this.attackFrame + 1}`;
            spriteManager.drawSprite(ctx, attackSprite, this.pos_x, this.pos_y);


            this.attackFrame++;
            if (this.attackFrame >= this.totalAttackFrames) {
                this.attacking = false;
                this.attackFrame = 0; // Сброс счетчика кадров атаки
            }
        } else {
            let spriteName = `enemy${Math.floor(this.frame / this.animationSpeed) + 1}`;
            spriteManager.drawSprite(ctx, spriteName, this.pos_x, this.pos_y);

            if (this.move_x !== 0 || this.move_y !== 0) {
                this.frame = (this.frame + 1) % (this.totalRunFrames * this.animationSpeed); // 6 - количество кадров обычной анимации
            } else {
                this.frame = 0; // Сброс анимации, если персонаж стоит на месте
            }
        }
    }

    update() { // на каждом шаге функция обнолвения для изменения состояния
        let result = physicManager.update(this, 1);

        // Добавим проверку и обновление пути к игроку
        if (gameManager.player !== null) {
            this.findPathToPlayer();
        }
    }

    moveTowards(tileX, tileY) {
        let currentTileX = Math.floor(this.pos_x / mapManager.tSize.x);
        let currentTileY = Math.floor(this.pos_y / mapManager.tSize.y);

        let deltaX = tileX - currentTileX;
        let deltaY = tileY - currentTileY;

        // Если враг находится не на целевом тайле, обновляем направление движения
        if (deltaX !== 0 || deltaY !== 0) {
            this.move_x = Math.sign(deltaX);
            this.move_y = Math.sign(deltaY);
        } else {
            this.move_x = 0;
            this.move_y = 0;
        }
    }


    findPathToPlayer() {
        // Получаем координаты начальной точки (где находится объект)
        let start = {
            x: Math.floor(this.pos_x / mapManager.tSize.x),
            y: Math.floor(this.pos_y / mapManager.tSize.y)
        };

        // Получаем координаты целевой точки (где находится игрок)
        let goal = {
            x: Math.floor(gameManager.player.pos_x / mapManager.tSize.x),
            y: Math.floor(gameManager.player.pos_y / mapManager.tSize.y)
        };

        // Ищем путь к игроку
        let path = this.findPath(start, goal);

        // Если найденный путь не пустой, двигаемся по нему
        if (path.length > 0) {
            // Пример: двигаться в направлении первой точки пути
            let nextTile = path[0]; // Получаем следующую точку пути
            this.moveTowards(nextTile.x, nextTile.y); // Двигаем объект к следующей точке пути
        }
    }

    // Функция эвристической оценки (для A* - оценка приближенности к цели)
    heuristic(a, b) {
        return Math.abs(a.x - b.x) + Math.abs(a.y - b.y);
    }

    findPath(start, goal) {
        // Реализация алгоритма A* для поиска пути
        let openSet = []; // Множество точек, которые предстоит рассмотреть
        let closedSet = []; // Множество точек, которые уже были рассмотрены
        let cameFrom = {};  // Хранит предыдущие точки, чтобы восстановить путь

        let gScore = {}; // Длина пути от стартовой точки до текущей
        let fScore = {}; // gScore + эвристическая оценка до цели

        openSet.push(start); // Начальная точка входит в множество открытых точек
        gScore[start.x + ',' + start.y] = 0; // Длина пути от начальной точки до себя равна 0
        fScore[start.x + ',' + start.y] = this.heuristic(start, goal); // Оценка от начальной точки до цели

        while (openSet.length > 0) { // Пока есть точки для рассмотрения
            let current = this.getMinFScore(openSet, fScore); // Выбор точки с минимальной fScore из openSet

            if (current.x === goal.x && current.y === goal.y) { // Если мы достигли целевой точки
                return this.reconstructPath(cameFrom, current); // Восстанавливаем путь до цели
            }

            // Обработка текущей точки
            // Если координаты x и y текущего узла совпадают с координатами x и y узла current,
            // этот узел исключается из openSet.
            openSet = openSet.filter(node => !(node.x === current.x && node.y === current.y));
            closedSet.push(current);

            let neighbors = this.getNeighbors(current); // Получаем соседей для текущей точки
            for (let neighbor of neighbors) { // Проходимся по соседям
                if (closedSet.some(node => node.x === neighbor.x && node.y === neighbor.y)) {
                    continue; // Если сосед уже в списке закрытых, пропускаем его
                }

                let tentativeGScore = gScore[current.x + ',' + current.y] + 1; // Длина пути через текущую точку

                if (!openSet.some(node => node.x === neighbor.x && node.y === neighbor.y)) {
                    openSet.push(neighbor); // Если сосед не в списке открытых, добавляем его туда
                } else if (tentativeGScore >= gScore[neighbor.x + ',' + neighbor.y]) {
                    continue; // Если это не улучшило путь, пропускаем
                }

                // Обновление данных о соседе (длина пути и оценка)
                cameFrom[neighbor.x + ',' + neighbor.y] = current;
                gScore[neighbor.x + ',' + neighbor.y] = tentativeGScore;
                fScore[neighbor.x + ',' + neighbor.y] = tentativeGScore + this.heuristic(neighbor, goal);
            }
        }

        return []; // Если путь не найден
    }

    getMinFScore(nodes, fScore) {
        let minNode = nodes[0]; // Начинаем с первого узла
        let minFScore = fScore[minNode.x + ',' + minNode.y]; // Получаем его fScore

        // Проходим по остальным узлам и ищем минимальный fScore
        for (let i = 1; i < nodes.length; i++) {
            let node = nodes[i];
            let score = fScore[node.x + ',' + node.y];
            // Если текущий score меньше минимального, обновляем значения
            if (score < minFScore) {
                minNode = node;
                minFScore = score;
            }
        }

        return minNode;
    }

    // получает всех соседей для указанного узла
    getNeighbors(node) {
        let neighbors = [];
        let directions = [{ x: 1, y: 0 }, { x: -1, y: 0 }, { x: 0, y: 1 }, { x: 0, y: -1 }];

        // Перебираем направления и получаем соседей для указанного узла
        for (let dir of directions) {
            let neighbor = { x: node.x + dir.x, y: node.y + dir.y }; // Вычисляем координаты соседа
            neighbors.push(neighbor); // Добавляем соседа в массив
        }

        return neighbors; // Возвращаем массив соседних узлов
    }

    //  восстанавливает путь
    reconstructPath(cameFrom, current) {
        let path = [];

        // Пока есть записи о предыдущих узлах, восстанавливаем путь
        while (cameFrom[current.x + ',' + current.y]) {
            path.unshift(current); // Добавляем текущий узел в начало пути
            current = cameFrom[current.x + ',' + current.y]; // Переходим к предыдущему узлу
        }
        return path; // Возвращаем восстановленный путь
    }


    die(){
        gameManager.entities.splice(gameManager.entities.indexOf(this), 1);
    }

    onTouchEntity(obj) {
        this.attacking = true;
        obj.action();
    }

    action() {
        gameManager.enemyAttack()
    }

}


export class Player extends Entity {
    constructor() {
        super();
        this.health = 150;
        this.speed = 2;
        this.move_x = 0;
        this.move_y = 0;
        this.damage = 3;
        this.frame = 0; // Счетчик кадров для анимации
        this.animationSpeed = 1; // Скорость анимации (меньше значение - быстрее анимация)
        this.attacking = false;
        this.attackFrame = 0;
        this.totalAttackFrames = 4;
        this.totalRunFrames = 6;
        this.attackRange = 20;
    }

    draw(ctx) {
        if (this.attacking) {
            let attackSprite = `playerAttack${this.attackFrame + 1}`;
            spriteManager.drawSprite(ctx, attackSprite, this.pos_x, this.pos_y);

            this.attackFrame++;
            if (this.attackFrame >= this.totalAttackFrames) {
                this.attacking = false;
                this.attackFrame = 0; // Сброс счетчика кадров атаки
            }
        } else {
            let spriteName = `player${Math.floor(this.frame / this.animationSpeed) + 1}`;
            spriteManager.drawSprite(ctx, spriteName, this.pos_x, this.pos_y);

            if (this.move_x !== 0 || this.move_y !== 0) {
                this.frame = (this.frame + 1) % (this.totalRunFrames * this.animationSpeed);
            } else {
                this.frame = 0; // Сброс анимации, если персонаж стоит на месте
            }
        }
    }

    attack(ctx) {
        spriteManager.drawSprite(ctx, "attack5", this.pos_x, this.pos_y);
    }

    onTouchEntity(obj) {
        obj.action();
    }

    action() {
        gameManager.enemyAttack();
    }

    update() {
        physicManager.update(this, 1);
    }

    die(){
        gameManager.entities.splice(gameManager.entities.indexOf(this), 1);
    }


}


export class BonusUpSpeed extends Entity {
    constructor() {
        super();
    }

    draw(ctx) {
        let spriteName = `upSpeed`;
        spriteManager.drawSprite(ctx, spriteName, this.pos_x, this.pos_y);
    }

    action() {
        console.log(gameManager.player.speed);
        gameManager.speedBonus();
        console.log(gameManager.player.speed);
       gameManager.entities.splice(gameManager.entities.indexOf(this), 1);
    }
}


export class BonusUpDmg extends Entity {
    constructor() {
        super();
    }

    draw(ctx) {
        let spriteName = `upDamage`; // Название спрайта бонуса
        spriteManager.drawSprite(ctx, spriteName, this.pos_x, this.pos_y);
    }

    action() {
        console.log(gameManager.player.damage);
        gameManager.damageBonus();
        console.log(gameManager.player.damage);
        gameManager.entities.splice(gameManager.entities.indexOf(this), 1);
    }

}
