const { SerialPort } = require('serialport')
const { ReadlineParser } = require('@serialport/parser-readline')

let debug = process.argv[2] == "-d";

const PORT = "COM6"

const port = new SerialPort({
    path: PORT,
    baudRate: 115200
})

const parser = port.pipe(new ReadlineParser())

parser.on('data', data => {
    console.log(data)

    if (!debug) {
        console.log(`established connection on port ${PORT}.`)
        process.exit()
    }
})

port.on("error", console.error)
parser.on("error", console.error)