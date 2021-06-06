const express = require('express')
const mongoose = require('mongoose')

const PostSchema = mongoose.Schema({
    title: {
        type: String,
        require: true
    },
    description: {
        type: String,
        require: true
    }
}, { timestamps: true })

const Post = mongoose.model('Posts', PostSchema)

const getAllPosts = async (req, res) => {
    const posts = await Post.find()
    try {
        res.json(posts)
    }
    catch(err) {
        res.json({message: err})
    }
}

const router = express.Router()

router
    .route('/')
    .get(getAllPosts)

module.exports = router;