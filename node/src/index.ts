import axios from 'axios'
import dayjs from 'dayjs'
import dotenv from 'dotenv'
import express, {type Request, type Response} from 'express'
import {Agent} from 'https'

import type {IPipe, IProject, IResponseData} from './types'

const app = express()
dotenv.config()
const PORT = Number(process.env.SERVER_PORT ?? 3535)

app.use(express.json())

const httpsAgent = new Agent({
	rejectUnauthorized: false
})

app.get('/check', async (req: Request, res: Response<IResponseData[]>) => {
	try {
		const projects = await axios
			.get<IProject[]>(`${process.env.GITLAB_HOST}/api/v4/projects`, {
				httpsAgent,
				headers: {Authorization: `Bearer ${process.env.GITLAB_TOKEN}`},
				params: {membership: true, per_page: 8, order_by: 'last_activity_at', sort: 'desc'}
			})
			.then(({data}) =>
				data.map(project => ({
					id: project.id,
					name: project.name,
					created_at: project.created_at,
					last_activity_at: project.last_activity_at
				}))
			)
		const results: IResponseData[] = []
		for (const project of projects) {
			try {
				const pipes = await axios
					.get<IPipe[]>(`${process.env.GITLAB_HOST}/api/v4/projects/${project.id}/pipelines`, {
						httpsAgent,
						headers: {Authorization: `Bearer ${process.env.GITLAB_TOKEN}`},
						params: {
							updated_after: dayjs().subtract(2, 'month').toISOString()
						}
					})
					.then(({data}) => data)

				const pipe = pipes.length ? pipes[0] : undefined
				const status = pipe?.status ?? 'no pipes'

				results.push({
					title: project.name,
					status
				})
			} catch (err) {
				results.push({
					title: project.name,
					status: 'pipeline error'
				})
			}
		}
		return res.json(results)
	} catch (error) {
		console.error('Axios error:', error)
		res.status(500).json([{title: 'error', status: 'Failed to fetch data'}])
	}
})

app.listen(PORT, () => {
	console.info(`🚀 Express server running on ${PORT} port`)
})
