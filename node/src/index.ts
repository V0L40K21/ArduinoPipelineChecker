import express, {type Request, type Response} from 'express'

const app = express()
const PORT = 3535

app.use(express.json())

interface IResponseData {
	title: string
	status: string
}

app.get('/check', (req: Request, res: Response<IResponseData[]>) => {
	res.json([
		{title: 'be_core', status: 'Done'},
		{title: 'fe_admin', status: 'Error'},
		{title: 'be_openway', status: 'In work'},
		{title: 'fe_schedule', status: 'In work'}
	])
})

app.listen(PORT, () => {
	console.info(`🚀 Express server running on ${PORT} port`)
})
