require('dotenv/config')
const express = require('express')
const mongoose = require('mongoose')
const cors = require('cors')
const bodyParser = require('body-parser')
const config = require('./config')

const postsRouter = require('./posts/post')

const app = express()

app.use(cors())
app.use(bodyParser.json())
app.use(express.json())

app.use('/api/posts', postsRouter)

mongoose.connect(config.DB_CONNECTION,
    {
        useUnifiedTopology: true,
        useNewUrlParser: true
    }, () => {
        console.log('Connected to the DB!')
    }
)

app.listen(config.HTTP_PORT, () => {
    console.log(`Server listening at http://localhost:${config.HTTP_PORT}`)
})