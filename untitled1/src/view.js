export default class View {
    static colorsPiece = {
        '1': 'green',
        '2': 'blue',
        '3': 'pink',
        '4': 'brown',
        '5': 'yellow',
        '6': 'purple',
        '7': 'orange',
    }

    constructor(element, width, height, rows, columns) {
        this.element = element;
        this.width = width;
        this.height = height;

        this.canvas = document.createElement('canvas');
        this.canvas.width = this.width;
        this.canvas.height = this.height;
        this.context = this.canvas.getContext('2d');
        this.playfiledBorderWidth = 8;

        this.playfiledX = this.playfiledBorderWidth;
        this.playfiledY = this.playfiledBorderWidth;

        this.playfiledWidth = this.width * 2 / 3;
        this.playfiledHeight = this.height;

        this.playfiledInWidth = this.playfiledWidth - this.playfiledBorderWidth * 2;
        this.playfiledInHeight = this.playfiledHeight - this.playfiledBorderWidth * 2;

        this.blockWidth = this.playfiledInWidth / columns;
        this.blockHeight = this.playfiledInHeight / rows;

        this.panelX = this.playfiledWidth + 15;
        this.panelY = 0;

        this.panelWidth = this.width / 3;
        this.panelHeight = this.height;

        this.element.appendChild(this.canvas);
    }

    render(state) {
        this.clearScreen();
        this.renderMainScreen(state);
        this.renderStats(state);
    }

    renderMainScreen({playfield}) {
        this.clearScreen();
        for (let y = 0; y < playfield.length; y++) {
            const line = playfield[y];
            for (let x = 0; x < line.length; x++) {
                const block = line[x];
                if (block) {
                    this.renderBlock(
                        this.playfiledX + (x * this.blockWidth),
                        this.playfiledY + (y * this.blockHeight),
                        this.blockWidth,
                        this.blockHeight,
                        View.colorsPiece[block]
                    );
                }
            }
        }
        this.context.strokeStyle = 'white';
        this.context.lineWidth = this.playfiledBorderWidth;
        this.context.strokeRect(0, 0, this.playfiledWidth, this.playfiledHeight);
    }

    clearScreen() {
        this.context.clearRect(0, 0, this.width, this.height);
    }

    renderStats({level, score, lines, nextPiece}) {
        this.context.fillStyle = 'white';
        this.context.font = '12px "Press Start 2P"';
        this.context.textAlign = 'start';
        this.context.textBaseline = 'top';
        this.context.fillText(`Score: ${score}`, this.panelX, this.panelY);
        this.context.fillText(`Lines: ${lines}`, this.panelX, this.panelY + 20);
        this.context.fillText(`Level: ${level}`, this.panelX, this.panelY + 40);
        this.context.fillText(`Next: `, this.panelX, this.panelY + 80);


        for (let y = 0; y < nextPiece.blocks.length; y++) {
            for (let x = 0; x < nextPiece.blocks[y].length; x++) {
                const block = nextPiece.blocks[y][x];
                if (block) {
                    this.renderBlock(this.panelX + (x * this.blockWidth), this.panelY + (y * this.blockHeight) + 100, this.blockWidth, this.blockHeight, View.colorsPiece[block]);
                }
            }
        }
    }


    renderStartScreen() {
        this.clearScreen();
        this.context.fillStyle = 'white';
        this.context.font = '12px "Press Start 2P"';
        this.context.textAlign = 'center';
        this.context.textBaseline = 'middle';
        this.context.fillText(
            'Press ENTER to Start',
            this.canvas.width / 2,
            this.canvas.height / 2
        );
    }




    renderEndScreen(state) {
        this.clearScreen();
        this.context.fillStyle = 'white';
        this.context.font = '12px "Press Start 2P"';
        this.context.textAlign = 'center';
        this.context.textBaseline = 'middle';
        this.context.fillText(
            `\`\`GAME OVER YOUR SCORE ${state.score}\`\``,
            this.canvas.width / 2,
            this.canvas.height / 2
        );
    }


    renderPauseScreen() {
        this.context.fillStyle = 'rgba(0,0,0,0.75)'; // затемнение
        this.context.fillRect(0, 0, this.width, this.height);
        this.context.fillStyle = 'white';
        this.context.font = '12px "Press Start 2P"';
        this.context.textAlign = 'center';
        this.context.textBaseline = 'middle';
        this.context.fillText(
            'Press ENTER to Resume',
            this.canvas.width / 2,
            this.canvas.height / 2
        );
    }

    renderBlock(x, y, width, height, blockColor) {
        this.context.fillStyle = blockColor;
        this.context.strokeStyle = 'white';
        this.context.lineWidth = 2;
        this.context.fillRect(x, y, width, height);
        this.context.strokeRect(x, y, width, height);
    }

}


