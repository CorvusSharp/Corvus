export default class Tetris {
    score = 0
    lines = 0
    level = 0
    playfield = this.createPlayfield()

    currentPiece = this.createPiece()
    nextPiece = this.createPiece()

    topOut = false

    createPlayfield() {
        const playfield = []

        for (let y = 0; y < 20; y++) {
            playfield[y] = []

            for (let x = 0; x < 10; x++) {
                playfield[y][x] = 0
            }
        }

        return playfield
    }
    get_lvl() {
        return this.lines > 0 ? Math.floor(this.lines * 0.1) : 0
    }


    resetPlayfield() {
        this.score = 0
        this.lines = 0
        this.level = 0
        this.playfield = this.createPlayfield()
        this.currentPiece = this.createPiece()
        this.nextPiece = this.createPiece()
        this.topOut = false
    }
    getState() {
        const playfield = this.playfield.map(row => [...row]);

        const {y: pieceY, x: pieceX, blocks} = this.currentPiece;

        // Копируем текущий игровой экран
        for (let y = 0; y < this.playfield.length; y++) {
            for (let x = 0; x < this.playfield[y].length; x++) {
                playfield[y][x] = this.playfield[y][x];
            }
        }


        for (let y = 0; y < blocks.length; y++) {
            for (let x = 0; x < blocks[y].length; x++) {
                if (blocks[y][x]) {
                    if (pieceY + y >= 0 && pieceY + y < playfield.length && pieceX + x >= 0 && pieceX + x < playfield[y].length) {
                        playfield[pieceY + y][pieceX + x] = blocks[y][x];
                    }
                }
            }
        }

        return {
            playfield,
            level: this.level,
            lines: this.lines,
            score: this.score,
            activePiece: this.currentPiece,
            nextPiece: this.nextPiece,
            isGameOver: this.topOut,

        };
    }


    moveLeft() {
        this.currentPiece.x -= 1;
        if (this.hashCol()) {
            this.currentPiece.x += 1;
        }
    }

    moveRight() {
        this.currentPiece.x += 1;
        if (this.hashCol()) {
            this.currentPiece.x -= 1;
        }
    }


    moveDown() {
        if (this.topOut) {
            return;
        }

        this.currentPiece.y += 1;

        if (this.hashCol()) {
            this.currentPiece.y -= 1;
            this.lockPiece();
            this.updatePieces();
            this.deleteLines();
            this.updateScore(this.lines);
            this.updateLevel();
            this.hashCol() ? this.topOut = true : null;
        }
    }

    hashCol() {
        const {y: pieceY, x: pieceX, blocks} = this.currentPiece;
        for (let y = 0; y < blocks.length; y++) {
            for (let x = 0; x < blocks[y].length; x++) {
                if (blocks[y][x] &&
                    ((this.playfield[pieceY + y] === undefined || this.playfield[pieceY + y][pieceX + x] === undefined) ||
                        this.playfield[pieceY + y][pieceX + x])) {
                    return true;
                }
            }
        }

        return false;
    }

    fastDrop() {
        if (this.topOut) {
            return;
        }
        while (!this.hashCol()) {
            this.currentPiece.y += 1;
        }
        this.currentPiece.y -= 1;
        this.topOut = this.hashCol();
    }


    createPiece() {
        const ind = Math.floor(Math.random() * 7);
        const type = "1234567"[ind];
        const piece = {};


        switch (type) {
            case '1':
                piece.blocks = [
                    [0, 0, 0, 0],
                    [1, 1, 1, 1],
                    [0, 0, 0, 0],
                    [0, 0, 0, 0],

                ];
                break;
            case '2':
                piece.blocks = [
                    [0, 0, 0],
                    [2, 2, 2],
                    [0, 0, 2],

                ];
                break;
            case '3':
                piece.blocks = [
                    [0, 0, 0],
                    [3, 3, 3],
                    [3, 0, 0],

                ];
                break;
            case '4':
                piece.blocks = [
                    [0, 0, 0],
                    [4, 4, ],
                    [4, 4, 0],

                ];
                break;
            case '5':
                piece.blocks = [
                    [0, 0, 0],
                    [0, 5, 5],
                    [5, 5, 0],

                ];
                break;
            case '6':
                piece.blocks = [
                    [0, 0, 0],
                    [6, 6, 6],
                    [0, 6, 0],

                ];
                break;
            case '7':
                piece.blocks = [
                    [0, 0, 0],
                    [7, 7, 0],
                    [0, 7, 7],

                ];
        }

        // фиксируем появление по центру
        piece.x = Math.floor((10 - piece.blocks[0].length) / 2);
        piece.y = -1;

        return piece;
    }


    lockPiece() {
        const {y: pieceY, x: pieceX, blocks} = this.currentPiece;

        for (let y = 0; y < blocks.length; y++) {
            if (this.playfield[pieceY + y] !== undefined) {
                for (let x = 0; x < blocks[y].length; x++) {
                    if (blocks[y][x] && this.playfield[pieceY + y][pieceX + x] !== undefined) {
                        this.playfield[pieceY + y][pieceX + x] = blocks[y][x];
                    }
                }
            }
        }
    }


    rotatePiece() {
        this.rotateBlocks();
        if (this.hashCol()) {
            this.rotateBlocks(false);
        }
    }

    rotateBlocks(clockwise = true) {
        const blocks = this.currentPiece.blocks;
        const length = blocks.length;

        const x = Math.floor(length / 2);
        const y = length - 1;

        for (let i = 0; i < x; i++) {
            for (let j = i; j < y - i; j++) {
                const temp = blocks[i][j];
                if (clockwise) {
                    blocks[i][j] = blocks[y - j][i];
                    blocks[y - j][i] = blocks[y - i][y - j];
                    blocks[y - i][y - j] = blocks[j][y - i];
                    blocks[j][y - i] = temp;
                } else {
                    blocks[i][j] = blocks[j][y - i];
                    blocks[j][y - i] = blocks[y - i][y - j];
                    blocks[y - i][y - j] = blocks[y - j][i];
                    blocks[y - j][i] = temp;
                }
            }
        }
    }

    deleteLines() {
        const rows = 20;
        const columns = 10;
        let lines = [];

        for (let y = rows - 1; y >= 0; y--) {
            let numberOfBlocks = 0;
            for (let x = 0; x < columns; x++) {
                if (this.playfield[y][x]) {
                    numberOfBlocks += 1;
                }
            }
            if (numberOfBlocks === 0) {
                break;
            } else if (numberOfBlocks < columns) {
                continue;
            } else if (numberOfBlocks === columns) {
                lines.unshift(y);
            }
            this.lines += 1;
        }

        for (let index of lines) {
            this.playfield.splice(index, 1);
            this.playfield.unshift(new Array(columns).fill(0));
            this.level = this.get_lvl()
        }

        return lines.length;

    }

    updateScore(lines) {
        lines = this.lines;
        if (lines > 0) {
            this.score = lines * 10 * (this.level + 1);
        }
    }

    updateLevel() {
        this.level = Math.floor(this.lines * 0.8);
    }
    updatePieces() {
        this.currentPiece = this.nextPiece;
        this.nextPiece = this.createPiece();
    }


}