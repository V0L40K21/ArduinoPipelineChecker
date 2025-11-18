export interface IResponseData {
	title: string
	status: string
}
export interface IProject {
	id: number
	name: string
	created_at: string
	last_activity_at: string
}
export interface IPipe {
	project_id: number
	status: string
}
